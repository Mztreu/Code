#include "FCCz.h"
#include <variant>
#include "E:\code\Lattice\Designer.h"

namespace Lattice
{
	class FCCz::FCCzImpl
	{
	public:
		FCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad);
		~FCCzImpl() noexcept;
		FCCzImpl(const FCCzImpl& other);
		FCCzImpl& operator = (const FCCzImpl& other);
		FCCzImpl(FCCzImpl&& other) noexcept;
		FCCzImpl& operator = (FCCzImpl&& other) noexcept;
		FCCzImpl() = delete;

	public:
		void Fill(const Vec3d& space, const std::string& file);

	private:
		Vec3d cellSize;
		double radius;
		int resol;
		int pad;
		Designer dsg;
		// should be as shown below
		//
		//        2 --------------------- 1
		//        /|                   /|
		//       / |                  / |
		//      /  |                 /  |
		//   3 ----|----------------- 4 |
		//     |   |                |   |
		//     |  6|----------------|---| 5
		//     |  /                 |  /
		//     | /                  | /
		//     |/                   |/
		//    7 -------------------- 8
		//
		//   z
		//   / \ / \  y
		//   |    /
		//   |   /
		//   | ______ > x (global, in structure)
		std::vector<Vec3d> box;
		std::vector<std::tuple<Vec3d, Vec3d>> keyPoints;
	};

	FCCz::FCCzImpl::FCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad)
	{
		this->cellSize = cellSize;
		this->radius = radius;
		this->resol = resol;
		this->pad = pad;

		box.emplace_back(cellSize.x() / 2., cellSize.y() / 2., cellSize.z() / 2);
		box.emplace_back(-cellSize.x() / 2., cellSize.y() / 2., cellSize.z() / 2);
		box.emplace_back(-cellSize.x() / 2., -cellSize.y() / 2., cellSize.z() / 2);
		box.emplace_back(cellSize.x() / 2., -cellSize.y() / 2., cellSize.z() / 2);
		box.emplace_back(cellSize.x() / 2., cellSize.y() / 2., -cellSize.z() / 2);
		box.emplace_back(-cellSize.x() / 2., cellSize.y() / 2., -cellSize.z() / 2);
		box.emplace_back(-cellSize.x() / 2., -cellSize.y() / 2., -cellSize.z() / 2);
		box.emplace_back(cellSize.x() / 2., -cellSize.y() / 2., -cellSize.z() / 2);

		dsg = Designer(cellSize, radius, resol, pad);

		keyPoints.emplace_back(box[0], box[4]);
		keyPoints.emplace_back(box[0], box[5]);
		keyPoints.emplace_back(box[0], box[7]);
		keyPoints.emplace_back(box[1], box[4]);
		keyPoints.emplace_back(box[1], box[5]);
		keyPoints.emplace_back(box[1], box[6]);
		keyPoints.emplace_back(box[2], box[5]);
		keyPoints.emplace_back(box[2], box[6]);
		keyPoints.emplace_back(box[2], box[7]);
		keyPoints.emplace_back(box[3], box[4]);
		keyPoints.emplace_back(box[3], box[6]);
		keyPoints.emplace_back(box[3], box[7]);

		dsg.Design(keyPoints);
	}

	FCCz::FCCzImpl::~FCCzImpl() noexcept = default;

	FCCz::FCCzImpl::FCCzImpl(const FCCzImpl& other)
	{
		if (this != &other)
		{

		}
	}

	FCCz::FCCzImpl& FCCz::FCCzImpl::operator=(const FCCzImpl& other)
	{
		if (this != &other)
		{

		}

		return *this;
	}

	FCCz::FCCzImpl::FCCzImpl(FCCzImpl&& other) noexcept = default;

	FCCz::FCCzImpl& FCCz::FCCzImpl::operator=(FCCzImpl&& other) noexcept = default;

	void FCCz::FCCzImpl::Fill(const Vec3d& space, const std::string& file)
	{
		dsg.Fill(space, file);
	}


	FCCz::FCCz(const Vec3d& cellSize, const double radius, const int resol, const int pad)
	{
		try
		{
			pImpl = std::make_unique<FCCzImpl>(cellSize, radius, resol, pad);
		}
		catch (const std::exception& e)
		{
			throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
		}
	}
	FCCz::~FCCz() noexcept = default;

	FCCz::FCCz(const FCCz& other)
	{
		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCCzImpl>(*other.pImpl);
				}
				catch (const std::exception& e)
				{
					throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
				}
			}
			else
				throw("[Error] Incomplete type!");
		}
	}

	FCCz& FCCz::operator=(const FCCz& other)
	{

		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCCzImpl>(*other.pImpl);
				}
				catch (const std::exception& e)
				{
					throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
				}
			}
			else
				throw("[Error] Incomplete type!");
		}
		return *this;
	}

	FCCz::FCCz(FCCz&& other) noexcept = default;

	FCCz& FCCz::operator=(FCCz&& other) noexcept = default;

	void FCCz::Fill(const Vec3d& space, const std::string& file) const
	{
		pImpl->Fill(space, file);
	}
}

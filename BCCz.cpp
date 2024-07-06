#include "BCCz.h"
#include <variant>
#include "Designer.h"

namespace Lattice
{
	class BCCz::BCCzImpl
	{
	public:
		BCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad);
		~BCCzImpl() noexcept;
		BCCzImpl(const BCCzImpl& other);
		BCCzImpl& operator = (const BCCzImpl& other);
		BCCzImpl(BCCzImpl&& other) noexcept;
		BCCzImpl& operator = (BCCzImpl&& other) noexcept;
		BCCzImpl() = delete;

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

	BCCz::BCCzImpl::BCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad)
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

		keyPoints.emplace_back(box[0], box[6]);
		keyPoints.emplace_back(box[1], box[7]);
		keyPoints.emplace_back(box[2], box[4]);
		keyPoints.emplace_back(box[3], box[5]);

		keyPoints.emplace_back(box[0], box[1]);
		keyPoints.emplace_back(box[1], box[2]);
		keyPoints.emplace_back(box[2], box[3]);
		keyPoints.emplace_back(box[3], box[0]);

		keyPoints.emplace_back(box[0], box[4]);
		keyPoints.emplace_back(box[1], box[5]);
		keyPoints.emplace_back(box[2], box[6]);
		keyPoints.emplace_back(box[3], box[7]);

		keyPoints.emplace_back(box[4], box[5]);
		keyPoints.emplace_back(box[5], box[6]);
		keyPoints.emplace_back(box[6], box[7]);
		keyPoints.emplace_back(box[7], box[4]);

		dsg.Design(keyPoints);
	}

	BCCz::BCCzImpl::~BCCzImpl() noexcept = default;

	BCCz::BCCzImpl::BCCzImpl(const BCCzImpl& other)
	{
		if (this != &other)
		{
			
		}
	}

	BCCz::BCCzImpl& BCCz::BCCzImpl::operator=(const BCCzImpl& other)
	{
		if (this != &other)
		{
			
		}

		return *this;
	}

	BCCz::BCCzImpl::BCCzImpl(BCCzImpl&& other) noexcept = default;

	BCCz::BCCzImpl& BCCz::BCCzImpl::operator=(BCCzImpl&& other) noexcept = default;

	void BCCz::BCCzImpl::Fill(const Vec3d& space, const std::string& file)
	{
		dsg.Fill(space, file);
	}


	BCCz::BCCz(const Vec3d& cellSize, const double radius, const int resol, const int pad)
	{
		try
		{
			pImpl = std::make_unique<BCCzImpl>(cellSize, radius, resol, pad);
		}
		catch (const std::exception& e)
		{
			throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
		}
	}
	BCCz::~BCCz() noexcept = default;

	BCCz::BCCz(const BCCz& other)
	{
		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<BCCzImpl>(*other.pImpl);
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

	BCCz& BCCz::operator=(const BCCz& other)
	{

		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<BCCzImpl>(*other.pImpl);
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

	BCCz::BCCz(BCCz&& other) noexcept = default;

	BCCz& BCCz::operator=(BCCz&& other) noexcept = default;

	void BCCz::Fill(const Vec3d& space, const std::string& file) const
	{
		pImpl->Fill(space, file);
	}
}

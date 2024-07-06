#include "S-FBCCz.h"
#include <variant>
#include "Designer.h"

namespace Lattice
{
	class S_FBCCz::S_FBCCzImpl
	{
	public:
		S_FBCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad);
		~S_FBCCzImpl() noexcept;
		S_FBCCzImpl(const S_FBCCzImpl& other);
		S_FBCCzImpl& operator = (const S_FBCCzImpl& other);
		S_FBCCzImpl(S_FBCCzImpl&& other) noexcept;
		S_FBCCzImpl& operator = (S_FBCCzImpl&& other) noexcept;
		S_FBCCzImpl() = delete;

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

	S_FBCCz::S_FBCCzImpl::S_FBCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad)
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

		keyPoints.emplace_back(box[1], box[4]);
		keyPoints.emplace_back(box[0], box[5]);
		keyPoints.emplace_back(box[2], box[5]);
		keyPoints.emplace_back(box[1], box[6]);
		keyPoints.emplace_back(box[2], box[7]);
		keyPoints.emplace_back(box[3], box[6]);
		keyPoints.emplace_back(box[3], box[4]);
		keyPoints.emplace_back(box[0], box[7]);

		keyPoints.emplace_back(box[0], box[4]);
		keyPoints.emplace_back(box[1], box[5]);
		keyPoints.emplace_back(box[2], box[6]);
		keyPoints.emplace_back(box[3], box[7]);

		dsg.Design(keyPoints);
	}

	S_FBCCz::S_FBCCzImpl::~S_FBCCzImpl() noexcept = default;

	S_FBCCz::S_FBCCzImpl::S_FBCCzImpl(const S_FBCCzImpl& other)
	{
		if (this != &other)
		{

		}
	}

	S_FBCCz::S_FBCCzImpl& S_FBCCz::S_FBCCzImpl::operator=(const S_FBCCzImpl& other)
	{
		if (this != &other)
		{

		}

		return *this;
	}

	S_FBCCz::S_FBCCzImpl::S_FBCCzImpl(S_FBCCzImpl&& other) noexcept = default;

	S_FBCCz::S_FBCCzImpl& S_FBCCz::S_FBCCzImpl::operator=(S_FBCCzImpl&& other) noexcept = default;

	void S_FBCCz::S_FBCCzImpl::Fill(const Vec3d& space, const std::string& file)
	{
		dsg.Fill(space, file);
	}


	S_FBCCz::S_FBCCz(const Vec3d& cellSize, const double radius, const int resol, const int pad)
	{
		try
		{
			pImpl = std::make_unique<S_FBCCzImpl>(cellSize, radius, resol, pad);
		}
		catch (const std::exception& e)
		{
			throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
		}
	}
	S_FBCCz::~S_FBCCz() noexcept = default;

	S_FBCCz::S_FBCCz(const S_FBCCz& other)
	{
		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<S_FBCCzImpl>(*other.pImpl);
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

	S_FBCCz& S_FBCCz::operator=(const S_FBCCz& other)
	{

		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<S_FBCCzImpl>(*other.pImpl);
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

	S_FBCCz::S_FBCCz(S_FBCCz&& other) noexcept = default;

	S_FBCCz& S_FBCCz::operator=(S_FBCCz&& other) noexcept = default;

	void S_FBCCz::Fill(const Vec3d& space, const std::string& file) const
	{
		pImpl->Fill(space, file);
	}
}
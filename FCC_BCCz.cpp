#include "FCC_BCCz.h"
#include <variant>
#include "E:\code\Lattice\Designer.h"

namespace Lattice
{
	class FCC_BCCz::FCC_BCCzImpl
	{
	public:
		FCC_BCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad);
		~FCC_BCCzImpl() noexcept;
		FCC_BCCzImpl(const FCC_BCCzImpl& other);
		FCC_BCCzImpl& operator = (const FCC_BCCzImpl& other);
		FCC_BCCzImpl(FCC_BCCzImpl&& other) noexcept;
		FCC_BCCzImpl& operator = (FCC_BCCzImpl&& other) noexcept;
		FCC_BCCzImpl() = delete;

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

	FCC_BCCz::FCC_BCCzImpl::FCC_BCCzImpl(const Vec3d& cellSize, const double radius, const int resol, const int pad)
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
		keyPoints.emplace_back(box[0], box[1]);
		keyPoints.emplace_back(box[1], box[2]);
		keyPoints.emplace_back(box[2], box[3]);
		keyPoints.emplace_back(box[3], box[0]);
		keyPoints.emplace_back(box[4], box[5]);
		keyPoints.emplace_back(box[5], box[6]);
		keyPoints.emplace_back(box[6], box[7]);
		keyPoints.emplace_back(box[7], box[4]);
		keyPoints.emplace_back(box[0], box[6]);
		keyPoints.emplace_back(box[1], box[7]);
		keyPoints.emplace_back(box[2], box[4]);
		keyPoints.emplace_back(box[3], box[5]);

		dsg.Design(keyPoints);
	}

	FCC_BCCz::FCC_BCCzImpl::~FCC_BCCzImpl() noexcept = default;

	FCC_BCCz::FCC_BCCzImpl::FCC_BCCzImpl(const FCC_BCCzImpl& other)
	{
		if (this != &other)
		{

		}
	}

	FCC_BCCz::FCC_BCCzImpl& FCC_BCCz::FCC_BCCzImpl::operator=(const FCC_BCCzImpl& other)
	{
		if (this != &other)
		{

		}

		return *this;
	}

	FCC_BCCz::FCC_BCCzImpl::FCC_BCCzImpl(FCC_BCCzImpl&& other) noexcept = default;

	FCC_BCCz::FCC_BCCzImpl& FCC_BCCz::FCC_BCCzImpl::operator=(FCC_BCCzImpl&& other) noexcept = default;

	void FCC_BCCz::FCC_BCCzImpl::Fill(const Vec3d& space, const std::string& file)
	{
		dsg.Fill(space, file);
	}


	FCC_BCCz::FCC_BCCz(const Vec3d& cellSize, const double radius, const int resol, const int pad)
	{
		try
		{
			pImpl = std::make_unique<FCC_BCCzImpl>(cellSize, radius, resol, pad);
		}
		catch (const std::exception& e)
		{
			throw(std::string(e.what()) + "\n[Error] Generating BCC Cell error!");
		}
	}
	FCC_BCCz::~FCC_BCCz() noexcept = default;

	FCC_BCCz::FCC_BCCz(const FCC_BCCz& other)
	{
		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCC_BCCzImpl>(*other.pImpl);
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

	FCC_BCCz& FCC_BCCz::operator=(const FCC_BCCz& other)
	{

		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCC_BCCzImpl>(*other.pImpl);
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

	FCC_BCCz::FCC_BCCz(FCC_BCCz&& other) noexcept = default;

	FCC_BCCz& FCC_BCCz::operator=(FCC_BCCz&& other) noexcept = default;

	void FCC_BCCz::Fill(const Vec3d& space, const std::string& file) const
	{
		pImpl->Fill(space, file);
	}
}

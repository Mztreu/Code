#include "FCC_BCCzCell.h"
#include "Base.h"
#include <opencascade/TopTools_ListOfShape.hxx>
#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
#include <opencascade/BRepPrimAPI_MakeSphere.hxx>
#include <opencascade/BRepBuilderAPI_Transform.hxx>
#include <vector>
#include <omp.h>

namespace lattice
{
	class FCC_BCCzCell::FCC_BCCzCellImpl
	{
	public:
		TopoDS_Shape GenCellSet(const Bnd_Box& box);
		gp_Vec3f GetSize();
		Standard_Real GetRadius();
		void SetSize(const gp_Vec3f& L);
		void SetRadius(const Standard_Real& R);

	public:
		FCC_BCCzCellImpl(const gp_Vec3f& L, const Standard_Real R);
		~FCC_BCCzCellImpl();
		FCC_BCCzCellImpl(const FCC_BCCzCellImpl& other);
		FCC_BCCzCellImpl& operator = (const FCC_BCCzCellImpl& other);

	private:
		FCC_BCCzCellImpl() = delete;

	private:
		gp_Vec3f L;
		Standard_Real R;
		enum Face { XOY, XOZ, YOZ };
		enum Pos { BOTTOM, TOP };
	private:
		TopoDS_Shape CellCent1();
		TopoDS_Shape CellCent2();
		TopoDS_Shape CellSide(const Face& face);
		TopoDS_Shape CellEdge(const Face& face);
		TopoDS_Shape CellCents1(std::vector<Standard_Integer> cellNum);
		TopoDS_Shape CellCents2(std::vector<Standard_Integer> cellNum);
		TopoDS_Shape CellSides(std::vector<Standard_Integer> cellNum);
		TopoDS_Shape CellEdges(std::vector<Standard_Integer> cellNum);
		TopoDS_Shape CellCorners(std::vector<Standard_Integer> cellNum);
	};
	TopoDS_Shape FCC_BCCzCell::FCC_BCCzCellImpl::GenCellSet(const Bnd_Box& box)
	{
		std::vector<Standard_Integer> cellNum = Base::CalCellNum(box, L);

		std::vector<TopoDS_Shape> bodyList(5);

		omp_set_nested(1);
#pragma omp parallel sections
		{
#pragma omp section
			{
				bodyList[0] = CellCents1(cellNum);
			}
#pragma omp section
			{
				bodyList[1] = CellCents2(cellNum);
			}
#pragma omp section
			{
				bodyList[2] = CellSides(cellNum);
			}
#pragma omp section
			{
				bodyList[3] = CellEdges(cellNum);
			}
#pragma omp section
			{
				bodyList[4] = CellCorners(cellNum);
			}
		}

		return Base::FuseShapes(bodyList);
	}

	TopoDS_Shape FCC_BCCzCell::FCC_BCCzCellImpl::CellCent1()
	{
		Standard_Real ML = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(3));
		gp_Vec3f offset = L / 2;
		std::vector<TopoDS_Shape> shapeList;
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ML).Shape());
		return Base::FuseShapes(shapeList);
	}

	TopoDS_Shape FCC_BCCzCell::FCC_BCCzCellImpl::CellCent2()
	{
		Standard_Real ML = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(3));
		Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 2;
		gp_Vec3f offset = L / 2;
		std::vector<TopoDS_Shape> shapeList;
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ML).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, 0)), R, LL).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, LL).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), 0)), R, LL).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, LL).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, LL).Shape());
		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
		return Base::FuseShapes(shapeList);
	}

	TopoDS_Shape FCC_BCCzCell::FCC_BCCzCellImpl::CellSide(const Face& face)
	{
		Standard_Real XL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 2;
		Standard_Real YL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(2));
		Standard_Real ZL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(3));
		gp_Vec3f offset = L / 2;
		std::vector<TopoDS_Shape> shapeList;

		if (face == Face::XOY)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, 0, offset.z())), R).Shape());
		}
		if (face == Face::XOZ)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, offset.y(), 0)), R).Shape());
		}
		if (face == Face::YOZ)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, offset.y(), 0)), R).Shape());
		}

		return Base::FuseShapes(shapeList);
	}
	
	TopoDS_Shape FCC_BCCzCell::FCC_BCCzCellImpl::CellEdge(const Face& face)
	{
		Standard_Real XL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 2;
		Standard_Real YL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(2));
		Standard_Real ZL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(3));
		gp_Vec3f offset = L / 2;
		std::vector<TopoDS_Shape> shapeList;
		if (face == Face::XOY)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), offset.y(), 0)), R).Shape());
		}
		if (face == Face::XOZ)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), 0, offset.z())), R).Shape());
		}
		if (face == Face::YOZ)
		{
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, 0)), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, XL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, -offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), -offset.z())), R, YL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), -offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), offset.y(), -offset.z())), R, ZL).Shape());
			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(0, -offset.y(), offset.z())), R).Shape());
		}

		return Base::FuseShapes(shapeList);
	}


	gp_Vec3f FCC_BCCzCell::FCC_BCCzCellImpl::GetSize()
	{
		return L;
	}

	Standard_Real FCC_BCCzCell::FCC_BCCzCellImpl::GetRadius()
	{
		return R;
	}

	void FCC_BCCzCell::FCC_BCCzCellImpl::SetSize(const gp_Vec3f& L)
	{
		this->L = L;
	}

	void FCC_BCCzCell::FCC_BCCzCellImpl::SetRadius(const Standard_Real& R)
	{
		this->R = R;
	}

	FCC_BCCzCell::FCC_BCCzCellImpl::FCC_BCCzCellImpl(const gp_Vec3f& L, const Standard_Real R)
	{
		this->L = L;
		this->R = R;
	}

	FCC_BCCzCell::FCC_BCCzCellImpl::~FCC_BCCzCellImpl() = default;

	FCC_BCCzCell::FCC_BCCzCellImpl::FCC_BCCzCellImpl(const FCC_BCCzCellImpl& other)
	{
		if (this != &other)
		{
			this->L = other.L;
			this->R = other.R;
		}
	}

	FCC_BCCzCell::FCC_BCCzCellImpl& FCC_BCCzCell::FCC_BCCzCellImpl::operator=(const FCC_BCCzCellImpl& other)
	{
		if (this != &other)
		{
			this->L = other.L;
			this->R = other.R;
		}

		return *this;
	}

	TopoDS_Shape FCC_BCCzCell::GenCellSet(const Bnd_Box& box)
	{
		return pImpl->GenCellSet(box);
	}

	gp_Vec3f FCC_BCCzCell::GetSize()
	{
		return pImpl->GetSize();
	}

	Standard_Real FCC_BCCzCell::GetRadius()
	{
		return pImpl->GetRadius();
	}

	void FCC_BCCzCell::SetSize(const gp_Vec3f& L)
	{
		pImpl->SetSize(L);
	}

	void FCC_BCCzCell::GetRadius(const Standard_Real& R)
	{
		pImpl->SetRadius(R);
	}

	FCC_BCCzCell::FCC_BCCzCell(const gp_Vec3f& L, const Standard_Real R)
	{
		try
		{
			pImpl = std::make_unique<FCC_BCCzCellImpl>(L, R);
		}
		catch (const std::exception& e)
		{
			std::cerr << "[Error] Generating BCC Cell error!" << std::endl;
			throw(e);
		}
	}
	FCC_BCCzCell::~FCC_BCCzCell() = default;

	FCC_BCCzCell::FCC_BCCzCell(const FCC_BCCzCell& other)
	{
		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCC_BCCzCellImpl>(*other.pImpl);
				}
				catch (const std::exception& e)
				{
					throw("[Error] Generating FCC_BCCz cell error!");
				}
			}
			else
				throw("[Error] Incomplete type!");
		}
	}

	FCC_BCCzCell& FCC_BCCzCell::operator=(const FCC_BCCzCell& other)
	{

		if (this != &other)
		{
			if (other.pImpl)
			{
				try
				{
					pImpl = std::make_unique<FCC_BCCzCellImpl>(*other.pImpl);
				}
				catch (const std::exception& e)
				{
					throw("[Error] Generating FCC_BCCz cell error!");
				}
			}
			else
				throw("[Error] Incomplete type!");
		}
		return *this;
	}
}
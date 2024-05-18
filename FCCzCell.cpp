//#include "FCCzCell.h"
//#include "Base.h"
//#include <opencascade/TopTools_ListOfShape.hxx>
//#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
//#include <opencascade/BRepPrimAPI_MakeSphere.hxx>
//#include <opencascade/BRepBuilderAPI_Transform.hxx>
//#include <vector>
//#include <omp.h>
//
//namespace lattice
//{
//	class FCCzCell::FCCzCellImpl
//	{
//	public:
//		TopoDS_Shape GenCellSet(const Bnd_Box& box);
//		gp_Vec3f GetSize();
//		Standard_Real GetRadius();
//		void SetSize(const gp_Vec3f& L);
//		void SetRadius(const Standard_Real& R);
//
//	public:
//		FCCzCellImpl(const gp_Vec3f& L, const Standard_Real R);
//		~FCCzCellImpl();
//		FCCzCellImpl(const FCCzCellImpl& other);
//		FCCzCellImpl& operator = (const FCCzCellImpl& other);
//
//	private:
//		FCCzCellImpl() = delete;
//
//	private:
//		gp_Vec3f L;
//		Standard_Real R;
//		enum Face { XOY, XOZ, YOZ };
//		enum Pos { BOTTOM, TOP };
//
//	private:
//		TopoDS_Shape CellCent();
//		TopoDS_Shape CellSide1(const Face& face);
//		TopoDS_Shape CellSide2(const Face& face);
//		TopoDS_Shape CellEdge1(const Face& face);
//		TopoDS_Shape CellEdge2(const Face& face);
//		TopoDS_Shape CellEdge3(const Face& face);
//		TopoDS_Shape CellCents(std::vector<Standard_Integer> cellNum);
//		TopoDS_Shape CellSides1(std::vector<Standard_Integer> cellNum);
//		TopoDS_Shape CellSides2(std::vector<Standard_Integer> cellNum);
//		TopoDS_Shape CellEdges1(std::vector<Standard_Integer> cellNum);
//		TopoDS_Shape CellEdges2(std::vector<Standard_Integer> cellNum);
//		TopoDS_Shape CellEdges3(std::vector<Standard_Integer> cellNum);
//		/*TopoDS_Shape CellBalls(std::vector<Standard_Integer> cellNum);*/
//	};
//
//	TopoDS_Shape FCCzCell::FCCzCellImpl::GenCellSet(const Bnd_Box& box)
//	{
//		std::vector<Standard_Integer> cellNum = Base::CalCellNum(box, L);
//
//		std::vector<TopoDS_Shape> bodyList(2);
//
//		omp_set_nested(1);
//#pragma omp parallel sections
//		{
//#pragma omp section
//			{
//				bodyList[0] = CellCents(cellNum);
//			}
////#pragma omp section
////			{
////				bodyList[1] = CellSides1(cellNum);
////			}
////#pragma omp section
////			{
////				bodyList[2] = CellSides2(cellNum);
////			}
////#pragma omp section
////			{
////				bodyList[3] = CellEdges1(cellNum);
////			}
////#pragma omp section
////			{
////				bodyList[4] = CellEdges2(cellNum);
////			}
////#pragma omp section
////			{
////				bodyList[5] = CellEdges3(cellNum);
////			}
////#pragma omp section
////			{
////				bodyList[6] = CellBalls(cellNum);
////			}
//		}
//
//		return Base::FuseShapes(bodyList);
//	}
//
//	TopoDS_Shape FCCzCell::FCCzCellImpl::CellCent()
//	{
//		Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 2;
//		Standard_Real ML = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2))/(2*Sqrt(2));
//		gp_Vec3f offset = L / 2;
//		std::vector<TopoDS_Shape> shapeList;
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, ML).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, ML).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, offset.z()), gp_Dir(-offset.x(), 0,-offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, -offset.z()), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, offset.z()), gp_Dir(offset.x(), 0, -offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), offset.z()), gp_Dir(0, -offset.y(), -offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), -offset.z()), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), offset.z()), gp_Dir(0, offset.y(), -offset.z())), R, LL).Shape());
//		return Base::FuseShapes(shapeList);
//	}
//
//	TopoDS_Shape FCCzCell::FCCzCellImpl::CellSide1(const Face& face)
//	{
//		Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 2;
//		Standard_Real ML = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / (2 * Sqrt(2));
//		gp_Vec3f offset = L / 2;
//		std::vector<TopoDS_Shape> shapeList;
//
//		/*if (face == Face::XOY)
//		{
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, 0), gp_Dir(-offset.x(), offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), offset.y(), 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, 0, offset.z())), R).Shape());
//		}
//		//侧棱不涉及到XOY面*/
//		if (face == Face::XOZ)
//		{
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, ML).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, ML).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, -offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), -offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(/*offset.x() / 2, offset.y() / 2, offset.z() / 2*/0,0,0), gp_Dir(0, offset.y(), 0)), R).Shape());
//		}
//		if (face == Face::YOZ)
//		{
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, ML).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, ML).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-offset.x(), 0, -offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, offset.y(), -offset.z())), R, LL).Shape());
//			shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(/*offset.x() / 2, offset.y() / 2, offset.z() / 2*/0, 0, 0), gp_Dir(0, offset.y(), 0)), R).Shape());
//		}
//
//		return Base::FuseShapes(shapeList);
//	}
//	//TopoDS_Shape FCCzCell::FCCzCellImpl::CellSide2(const Face& face)
//	//{
//	//	Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 4;
//	//	gp_Vec3f offset = L / 2;
//	//	std::vector<TopoDS_Shape> shapeList;
//
//	//	//if (face == Face::XOY)
//	//	//{
//	//	//	shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), offset.y(), offset.z())), R, LL).Shape());
//	//	//	shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, 0), gp_Dir(-offset.x(), offset.y(), offset.z())), R, LL).Shape());
//	//	//	shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//	//	shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), offset.y(), 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//	//	shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, 0, offset.z())), R).Shape());
//	//	//}
//	//	////侧棱不涉及到XOY面
//	//	if (face == Face::XOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, offset.z()), gp_Dir(-offset.x(), 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), offset.z()), gp_Dir(0, -offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), offset.z()), gp_Dir(0, offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), -offset.z()), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(0, offset.y(), 0)), R).Shape());
//	//	}
//	//	if (face == Face::YOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, offset.z()), gp_Dir(-offset.x(), 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), offset.z()), gp_Dir(0, -offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, offset.z()), gp_Dir(offset.x(), 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, -offset.z()), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), 0, 0)), R).Shape());
//	//	}
//
//	//	return Base::FuseShapes(shapeList);
//	//}
//
//	//TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdge1(const Face& face)
//	//{
//	//	Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 4;
//	//	gp_Vec3f offset = L / 2;
//	//	std::vector<TopoDS_Shape> shapeList;
//	//	/*if (face == Face::XOY)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, offset.z()), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), -offset.y(), 0)), R).Shape());
//	//	}*/
//	//	if (face == Face::XOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), 0, offset.z())), R).Shape());
//	//	}
//	//	if (face == Face::YOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), -offset.z()), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(0, -offset.y(), offset.z())), R).Shape());
//	//	}
//
//	//	return Base::FuseShapes(shapeList);
//	//}
//
//	//TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdge2(const Face& face)
//	//{
//	//	Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 4;
//	//	gp_Vec3f offset = L / 2;
//	//	std::vector<TopoDS_Shape> shapeList;
//	//	/*if (face == Face::XOY)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, offset.z()), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), -offset.y(), 0)), R).Shape());
//	//	}*/
//	//	if (face == Face::XOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, -offset.z()), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), 0, offset.z())), R).Shape());
//	//	}
//	//	if (face == Face::YOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), -offset.z()), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(0, -offset.y(), offset.z())), R).Shape());
//	//	}
//
//	//	return Base::FuseShapes(shapeList);
//	//}
//
//	//TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdge3(const Face& face)
//	//{
//	//	Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 4;
//	//	gp_Vec3f offset = L / 2;
//	//	std::vector<TopoDS_Shape> shapeList;
//	//	/*if (face == Face::XOY)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, offset.z()), gp_Dir(offset.x(), -offset.y(), -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), -offset.y(), 0)), R).Shape());
//	//	}*/
//	//	if (face == Face::XOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, -offset.y(), -offset.z()), gp_Dir(0, offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, offset.y(), -offset.z()), gp_Dir(0, -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, -offset.z()), gp_Dir(-offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-offset.x(), 0, -offset.z()), gp_Dir(offset.x(), 0, offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, offset.y() / 2, offset.z() / 2), gp_Dir(offset.x(), 0, offset.z())), R).Shape());
//	//	}
//	//	/*if (face == Face::YOZ)
//	//	{
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(offset.x(), 0, 0), gp_Dir(-offset.x(), -offset.y(), offset.z())), R, LL).Shape());
//	//		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(offset.x() / 2, -offset.y() / 2, offset.z() / 2), gp_Dir(0, -offset.y(), offset.z())), R).Shape());
//	//	}*/
//
//	//	return Base::FuseShapes(shapeList);
//	//}
//
//	TopoDS_Shape FCCzCell::FCCzCellImpl::CellCents(std::vector<Standard_Integer> cellNum)
//	{
//		TopoDS_Shape center = CellCent();
//		const int xn = cellNum[0];
//		const int yn = cellNum[1];
//		const int zn = cellNum[2];
//		const int xxn = cellNum[0]/* - 1*/;
//		const int yyn = cellNum[1]/* - 1*/;
//		const int zzn = cellNum[2] /*- 1*/;
//		std::vector<TopoDS_Shape> shapeList(xn * yn * zn + xxn * yyn * zzn);
//#pragma omp parallel for
//		for (Standard_Integer z = 0; z < zn; z++)
//		{
//			for (Standard_Integer y = 0; y < yn; y++)
//			{
//				for (Standard_Integer x = 0; x < xn; x++)
//				{
//					gp_Trsf trsf;
//					trsf.SetTranslation(gp_Vec(x * L.x(), y * L.y(), z * L.z()));
//					shapeList[x + y /** xn*/ + z /** yn * xn*/] = BRepBuilderAPI_Transform(center, trsf).Shape();
//
//					if (x < xxn && y < yyn && z < zzn)
//					{
//						trsf.SetTranslation(gp_Vec((x /*+ 0.5*/) * L.x(), (y /*+ 1*/) * L.y(), (z /*+ 0.5*/) * L.z()));
//						shapeList[xn * yn * zn + x + y * xxn + z * yyn * xxn] = BRepBuilderAPI_Transform(center, trsf).Shape();
//					}
//				}
//			}
//		}
//		return Base::FuseShapes(shapeList);
//	}
//
////	TopoDS_Shape FCCzCell::FCCzCellImpl::CellSides1(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector<TopoDS_Shape> sideList(2);
////
////#pragma omp parallel sections
////		{
//////#pragma omp section
//////			{
//////				const int xn = cellNum[0] - 1;
//////				const int yn = cellNum[1] - 1;
//////				std::vector<TopoDS_Shape> shapeList(xn * yn * 2);
//////				TopoDS_Shape cellSide1 = CellSide1(Face::XOY);
//////#pragma omp parallel for
//////				for (int y = 0; y < yn; ++y)
//////				{
//////					for (int x = 0; x < xn; ++x)
//////					{
//////						gp_Trsf trsf;
//////						trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
//////						shapeList[x + y * xn] = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
//////						trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
//////						TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
//////						trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (y + 0.5) * L.y(), 0));
//////						shapeList[xn * yn + x + y * xn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					}
//////				}
//////				sideList[0] = Base::FuseShapes(shapeList);
//////			}
////
////#pragma omp section
////			{
////				const int xn = cellNum[0] /*- 1*/;
////				const int zn = cellNum[2] /*- 1*/;
////				std::vector<TopoDS_Shape> shapeList(xn * zn * 2);
////				TopoDS_Shape cellSide1 = CellSide1(Face::XOZ);
////#pragma omp parallel for 
////				for (int z = 0; z < zn; ++z)
////				{
////					for (int x = 0; x < xn; ++x)
////					{
////						gp_Trsf trsf;
////						trsf.SetTranslation(gp_Vec((x/* + 0.5*/) * L.x(), (cellNum[1] /*- 0.5*/) * L.y(), (z /*+ 0.5*/) * L.z()));
////						shapeList[x + z * zn] = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
////						trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 1)));//沿x轴翻转
////						TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
////						trsf.SetTranslation(gp_Vec((x /*+ 0.5*/) * L.x(), 0, (z /*+ 0.5*/) * L.z()));
////						shapeList[xn * zn + x + z * xn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					}
////				}
////				sideList[0] = Base::FuseShapes(shapeList);
////			}
////
////#pragma omp section
////			{
////				const int yn = cellNum[1] /*- 1*/;
////				const int zn = cellNum[2]/* - 1*/;
////				std::vector<TopoDS_Shape> shapeList(yn * zn * 2);
////				TopoDS_Shape cellSide1 = CellSide1(Face::YOZ);
////#pragma omp parallel for 
////				for (int z = 0; z < zn; ++z)
////				{
////					for (int y = 0; y < yn; ++y)
////					{
////						gp_Trsf trsf;
////						trsf.SetTranslation(gp_Vec((cellNum[0] /*- 0.5*/) * L.x(), (y /*+ 0.5*/) * L.y(), (z /*+ 0.5*/) * L.z()));
////						shapeList[y + z * yn] = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
////						trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 1)));//沿x轴翻转
////						TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide1, trsf).Shape();
////						trsf.SetTranslation(gp_Vec(0, (y /*+ 0.5*/) * L.y(), (z /*+ 0.5*/) * L.z()));
////						shapeList[yn * zn + y + z * yn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					}
////				}
////				sideList[1] = Base::FuseShapes(shapeList);
////			}
////		}
////		return Base::FuseShapes(sideList);
////	}
////	
////	TopoDS_Shape FCCzCell::FCCzCellImpl::CellSides2(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector<TopoDS_Shape> sideList(3);
////
////#pragma omp parallel sections
////		{
////			/*#pragma omp section
////						{
////							const int xn = cellNum[0] - 1;
////							const int yn = cellNum[1] - 1;
////							std::vector<TopoDS_Shape> shapeList(xn * yn * 2);
////							TopoDS_Shape cellSide2 = CellSide2(Face::XOY);
////			#pragma omp parallel for
////							for (int y = 0; y < yn; ++y)
////							{
////								for (int x = 0; x < xn; ++x)
////								{
////									gp_Trsf trsf;
////									trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////									shapeList[x + y * xn] = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////									trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////									TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////									trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (y + 0.5) * L.y(), 0));
////									shapeList[xn * yn + x + y * xn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////								}
////							}
////							sideList[0] = Base::FuseShapes(shapeList);
////						}*/
////
////#pragma omp section
////			{
////				const int xn = cellNum[0] - 1;
////				const int zn = cellNum[2] - 1;
////				std::vector<TopoDS_Shape> shapeList(xn * zn * 2);
////				TopoDS_Shape cellSide2 = CellSide2(Face::XOZ);
////#pragma omp parallel for 
////				for (int z = 0; z < zn; ++z)
////				{
////					for (int x = 0; x < xn; ++x)
////					{
////						gp_Trsf trsf;
////						trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
////						shapeList[x + z * zn] = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////						trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));//沿y轴翻转
////						TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////						trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, (z + 0.5) * L.z()));
////						shapeList[xn * zn + x + z * xn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					}
////				}
////				sideList[1] = Base::FuseShapes(shapeList);
////			}
////
////#pragma omp section
////			{
////				const int yn = cellNum[1] - 1;
////				const int zn = cellNum[2] - 1;
////				std::vector<TopoDS_Shape> shapeList(yn * zn * 2);
////				TopoDS_Shape cellSide2 = CellSide2(Face::YOZ);
////#pragma omp parallel for 
////				for (int z = 0; z < zn; ++z)
////				{
////					for (int y = 0; y < yn; ++y)
////					{
////						gp_Trsf trsf;
////						trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), (z + 0.5) * L.z()));
////						shapeList[y + z * yn] = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////						trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));//沿x轴翻转
////						TopoDS_Shape shape = BRepBuilderAPI_Transform(cellSide2, trsf).Shape();
////						trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), (z + 0.5) * L.z()));
////						shapeList[yn * zn + y + z * yn] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					}
////				}
////				sideList[2] = Base::FuseShapes(shapeList);
////			}
////		}
////		return Base::FuseShapes(sideList);
////	}
////
////	TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdges1(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector <TopoDS_Shape> edgeList(3);
////
////#pragma omp parallel sections
////		{
////#pragma omp section
////			{
////				const int zn = cellNum[2] - 1;
////				std::vector<TopoDS_Shape> shapeList(zn * 4);
////				TopoDS_Shape cellEdge1 = CellEdge1(Face::XOY);
////#pragma omp parallel for
////				for (int z = 0; z < zn; ++z)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), 0, (z + 0.5) * L.z()));
////					shapeList[z] = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
////					shapeList[zn + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, 0, (z + 0.5) * L.z()));
////					shapeList[zn * 2 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
////					shapeList[zn * 3 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[0] = Base::FuseShapes(shapeList);
////			}
////
////#pragma omp section
////			{
////				const int yn = cellNum[1] - 1;
////				std::vector<TopoDS_Shape> shapeList(yn * 4);
////				TopoDS_Shape cellEdge1 = CellEdge1(Face::XOZ);
////#pragma omp parallel for
////				for (int y = 0; y < cellNum[1] - 1; ++y)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[y] = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[yn + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), 0));
////					shapeList[yn * 2 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), 0));
////					shapeList[yn * 3 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[1] = Base::FuseShapes(shapeList);
////			}
////
////
////
////#pragma omp section
////			{
////				const int xn = cellNum[0] - 1;
////				std::vector<TopoDS_Shape> shapeList(xn * 4);
////				TopoDS_Shape cellEdge1 = CellEdge1(Face::YOZ);
////#pragma omp parallel for
////				for (int x = 0; x < cellNum[0] - 1; ++x)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, (cellNum[2] - 0.5) * L.z()));
////					shapeList[x] = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[xn + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, 0));
////					shapeList[xn * 2 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge1, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), 0));
////					shapeList[xn * 3 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[2] = Base::FuseShapes(shapeList);
////			}
////		}
////		return Base::FuseShapes(edgeList);
////	}
//
////	TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdges2(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector <TopoDS_Shape> edgeList(3);
////
////#pragma omp parallel sections
////		{
//////#pragma omp section
//////			{
//////				const int zn = cellNum[2] - 1;
//////				std::vector<TopoDS_Shape> shapeList(zn * 4);
//////				TopoDS_Shape cellEdge2 = CellEdge2(Face::XOY);
//////#pragma omp parallel for
//////				for (int z = 0; z < zn; ++z)
//////				{
//////					gp_Trsf trsf;
//////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), 0, (z + 0.5) * L.z()));
//////					shapeList[z] = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
//////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
//////					shapeList[zn + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
//////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec(0, 0, (z + 0.5) * L.z()));
//////					shapeList[zn * 2 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI);
//////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec(0, (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
//////					shapeList[zn * 3 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////				}
//////				edgeList[0] = Base::FuseShapes(shapeList);
//////			}
////
////#pragma omp section
////			{
////				const int yn = cellNum[1] - 1;
////				std::vector<TopoDS_Shape> shapeList(yn * 4);
////				TopoDS_Shape cellEdge2 = CellEdge2(Face::XOZ);
////#pragma omp parallel for
////				for (int y = 0; y < cellNum[1] - 1; ++y)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[y] = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[yn + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), 0));
////					shapeList[yn * 2 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), 0));
////					shapeList[yn * 3 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[1] = Base::FuseShapes(shapeList);
////			}
////
////
////
////#pragma omp section
////			{
////				const int xn = cellNum[0] - 1;
////				std::vector<TopoDS_Shape> shapeList(xn * 4);
////				TopoDS_Shape cellEdge2 = CellEdge2(Face::YOZ);
////#pragma omp parallel for
////				for (int x = 0; x < cellNum[0] - 1; ++x)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, (cellNum[2] - 0.5) * L.z()));
////					shapeList[x] = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[xn + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, 0));
////					shapeList[xn * 2 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge2, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), 0));
////					shapeList[xn * 3 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[2] = Base::FuseShapes(shapeList);
////			}
////		}
////		return Base::FuseShapes(edgeList);
////	}
////
////	TopoDS_Shape FCCzCell::FCCzCellImpl::CellEdges3(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector <TopoDS_Shape> edgeList(3);
////
////#pragma omp parallel sections
////		{
//////#pragma omp section
//////			{
//////				const int zn = cellNum[2] - 1;
//////				std::vector<TopoDS_Shape> shapeList(zn * 4);
//////				TopoDS_Shape cellEdge3 = CellEdge3(Face::XOY);
//////#pragma omp parallel for
//////				for (int z = 0; z < zn; ++z)
//////				{
//////					gp_Trsf trsf;
//////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), 0, (z + 0.5) * L.z()));
//////					shapeList[z] = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
//////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
//////					shapeList[zn + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
//////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec(0, 0, (z + 0.5) * L.z()));
//////					shapeList[zn * 2 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI);
//////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec(0, (cellNum[1] - 0.5) * L.y(), (z + 0.5) * L.z()));
//////					shapeList[zn * 3 + z] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////				}
//////				edgeList[0] = Base::FuseShapes(shapeList);
//////			}
////
////#pragma omp section
////			{
////				const int yn = cellNum[1] - 1;
////				std::vector<TopoDS_Shape> shapeList(yn * 4);
////				TopoDS_Shape cellEdge3 = CellEdge3(Face::XOZ);
////#pragma omp parallel for
////				for (int y = 0; y < cellNum[1] - 1; ++y)
////				{
////					gp_Trsf trsf;
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[y] = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
////					shapeList[yn + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
////					trsf.SetTranslation(gp_Vec((cellNum[0] - 0.5) * L.x(), (y + 0.5) * L.y(), 0));
////					shapeList[yn * 2 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), M_PI);
////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
////					trsf.SetTranslation(gp_Vec(0, (y + 0.5) * L.y(), 0));
////					shapeList[yn * 3 + y] = BRepBuilderAPI_Transform(shape, trsf).Shape();
////				}
////				edgeList[1] = Base::FuseShapes(shapeList);
////			}
////
////
////
//////#pragma omp section
//////			{
//////				const int xn = cellNum[0] - 1;
//////				std::vector<TopoDS_Shape> shapeList(xn * 4);
//////				TopoDS_Shape cellEdge3 = CellEdge3(Face::YOZ);
//////#pragma omp parallel for
//////				for (int x = 0; x < cellNum[0] - 1; ++x)
//////				{
//////					gp_Trsf trsf;
//////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, (cellNum[2] - 0.5) * L.z()));
//////					shapeList[x] = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
//////					TopoDS_Shape shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), (cellNum[2] - 0.5) * L.z()));
//////					shapeList[xn + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
//////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), 0, 0));
//////					shapeList[xn * 2 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////					trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), M_PI);
//////					shape = BRepBuilderAPI_Transform(cellEdge3, trsf).Shape();
//////					trsf.SetTranslation(gp_Vec((x + 0.5) * L.x(), (cellNum[1] - 0.5) * L.y(), 0));
//////					shapeList[xn * 3 + x] = BRepBuilderAPI_Transform(shape, trsf).Shape();
//////				}
//////				edgeList[2] = Base::FuseShapes(shapeList);
//////			}
////		}
////		return Base::FuseShapes(edgeList);
////	}
////
////	/*TopoDS_Shape FCCzCell::FCCzCellImpl::CellBalls(std::vector<Standard_Integer> cellNum)
////	{
////		std::vector<TopoDS_Shape> shapeList;
////		Standard_Real LL = Sqrt(Pow(L.x(), 2) + Pow(L.y(), 2) + Pow(L.z(), 2)) / 4;
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(-L.x(), -L.y(), -L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.5), 0, 0), gp_Dir(L.x(), -L.y(), -L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, L.y() * (cellNum[1] - 0.5), 0), gp_Dir(-L.x(), L.y(), -L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.5), L.y() * (cellNum[1] - 0.5), 0), gp_Dir(L.x(), L.y(), -L.z())), R, LL).Shape());
////
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, L.z() * (cellNum[2] - 0.5)), gp_Dir(-L.x(), -L.y(), L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.5), 0, L.z() * (cellNum[2] - 0.5)), gp_Dir(L.x(), -L.y(), L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, L.y() * (cellNum[1] - 0.5), L.z() * (cellNum[2] - 0.5)), gp_Dir(-L.x(), L.y(), L.z())), R, LL).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.5), L.y() * (cellNum[1] - 0.5), L.z() * (cellNum[0] - 0.5)), gp_Dir(L.x(), L.y(), L.z())), R, LL).Shape());
////
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(-L.x() / 4, -L.y() / 4, -L.z() / 4), gp_Dir(-L.x(), -L.y(), -L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.25), -L.y() / 4, -L.z() / 4), gp_Dir(L.x(), -L.y(), -L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(-L.x() / 4, L.y() * (cellNum[1] - 0.25), -L.z() / 4), gp_Dir(-L.x(), L.y(), -L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.25), L.y() * (cellNum[1] - 0.25), -L.z() / 4), gp_Dir(L.x(), L.y(), -L.z())), R).Shape());
////
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(-L.x() / 4, -L.y() / 4, L.z() * (cellNum[2] - 0.25)), gp_Dir(-L.x(), -L.y(), L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.25), -L.y() / 4, L.z() * (cellNum[2] - 0.25)), gp_Dir(L.x(), -L.y(), L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(-L.x() / 4, L.y() * (cellNum[1] - 0.25), L.z() * (cellNum[2] - 0.25)), gp_Dir(-L.x(), L.y(), L.z())), R).Shape());
////		shapeList.push_back(BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(L.x() * (cellNum[0] - 0.25), L.y() * (cellNum[1] - 0.25), L.z() * (cellNum[2] - 0.25)), gp_Dir(L.x(), L.y(), L.z())), R).Shape());
////
////		return Base::FuseShapes(shapeList);
////	}*/
//
//	gp_Vec3f FCCzCell::FCCzCellImpl::GetSize()
//	{
//		return L;
//	}
//
//	Standard_Real FCCzCell::FCCzCellImpl::GetRadius()
//	{
//		return R;
//	}
//
//	void FCCzCell::FCCzCellImpl::SetSize(const gp_Vec3f& L)
//	{
//		this->L = L;
//	}
//
//	void FCCzCell::FCCzCellImpl::SetRadius(const Standard_Real& R)
//	{
//		this->R = R;
//	}
//
//	FCCzCell::FCCzCellImpl::FCCzCellImpl(const gp_Vec3f& L, const Standard_Real R)
//	{
//		this->L = L;
//		this->R = R;
//	}
//
//	FCCzCell::FCCzCellImpl::~FCCzCellImpl() = default;
//
//	FCCzCell::FCCzCellImpl::FCCzCellImpl(const FCCzCellImpl& other)
//	{
//		if (this != &other)
//		{
//			this->L = other.L;
//			this->R = other.R;
//		}
//	}
//
//	FCCzCell::FCCzCellImpl& FCCzCell::FCCzCellImpl::operator=(const FCCzCellImpl& other)
//	{
//		if (this != &other)
//		{
//			this->L = other.L;
//			this->R = other.R;
//		}
//
//		return *this;
//	}
//
//	TopoDS_Shape FCCzCell::GenCellSet(const Bnd_Box& box)
//	{
//		return pImpl->GenCellSet(box);
//	}
//
//	gp_Vec3f FCCzCell::GetSize()
//	{
//		return pImpl->GetSize();
//	}
//
//	Standard_Real FCCzCell::GetRadius()
//	{
//		return pImpl->GetRadius();
//	}
//
//	void FCCzCell::SetSize(const gp_Vec3f& L)
//	{
//		pImpl->SetSize(L);
//	}
//
//	void FCCzCell::GetRadius(const Standard_Real& R)
//	{
//		pImpl->SetRadius(R);
//	}
//
//	FCCzCell::FCCzCell(const gp_Vec3f& L, const Standard_Real R)
//	{
//		try
//		{
//			pImpl = std::make_unique<FCCzCellImpl>(L, R);
//		}
//		catch (const std::exception& e)
//		{
//			std::cerr << "[Error] Generating BCC Cell error!" << std::endl;
//			throw(e);
//		}
//	}
//	FCCzCell::~FCCzCell() = default;
//
//	FCCzCell::FCCzCell(const FCCzCell& other)
//	{
//		if (this != &other)
//		{
//			if (other.pImpl)
//			{
//				try
//				{
//					pImpl = std::make_unique<FCCzCellImpl>(*other.pImpl);
//				}
//				catch (const std::exception& e)
//				{
//					throw("[Error] Generating FCCz cell error!");
//				}
//			}
//			else
//				throw("[Error] Incomplete type!");
//		}
//	}
//
//	FCCzCell& FCCzCell::operator=(const FCCzCell& other)
//	{
//
//		if (this != &other)
//		{
//			if (other.pImpl)
//			{
//				try
//				{
//					pImpl = std::make_unique<FCCzCellImpl>(*other.pImpl);
//				}
//				catch (const std::exception& e)
//				{
//					throw("[Error] Generating FCCz cell error!");
//				}
//			}
//			else
//				throw("[Error] Incomplete type!");
//		}
//		return *this;
//	}
//}
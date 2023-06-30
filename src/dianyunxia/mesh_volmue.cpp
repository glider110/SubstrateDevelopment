/*
 * @Author: glider
 * @Date: 2023-06-30 10:26:54
 * @LastEditTime: 2023-06-30 10:42:27
 * @FilePath: /SubstrateDevelopment/src/dianyunxia/mesh_volmue.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2023 by  ${git_email}, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>
#include <vtkPLYReader.h>
#include <vtkTriangleFilter.h>
#include <vtkMassProperties.h>
#include <vtkSmartPointer.h>
//可视化相关头文件
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>
#include <vtkAutoInit.h> 
#include <vtkActor.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

using namespace std;

int main(int argc, char** argv)
{
    vtkSmartPointer<vtkPLYReader> reader = vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName("UV.ply");
    reader->Update();
	vtkSmartPointer<vtkTriangleFilter> tri = vtkSmartPointer<vtkTriangleFilter>::New();
	tri->SetInputData(reader->GetOutput());
	tri->Update();
	vtkSmartPointer<vtkMassProperties> poly = vtkSmartPointer<vtkMassProperties>::New();
	poly->SetInputData(tri->GetOutput());
	poly->Update();

	double vol = poly->GetVolume();//体积
	double area = poly->GetSurfaceArea();//表面积
    double maxArea = poly->GetMaxCellArea();//最大单元面积
	double minArea = poly->GetMinCellArea();//最小单元面积
	cout << "体积为：" << vol << endl;
	cout << "表面积为：" << area << endl;
	//============================可视化==========================
	//---------------用于渲染多边形几何数据-------------------
	vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cylinderMapper->SetInputConnection(reader->GetOutputPort()); 
	vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->GetProperty()->SetColor(1.0, 0.75, 0.0);
	//-----------------管理场景渲染过程-----------------------
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(1.0, 1.0, 1.0);
	//-------------------设置窗口参数------------------------
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(640, 480);//设置窗口大小，以像素为单元
	renWin->Render();
	renWin->SetWindowName("Render");
	//---------------------交互机制--------------------------
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();
	//======================可视化结束===========================
    system("pause");

    return (0);
}


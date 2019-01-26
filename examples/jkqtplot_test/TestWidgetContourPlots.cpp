#include "TestWidgetContourPlots.h"
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <QApplication>





TestWidgetContourPlots::TestWidgetContourPlots(QWidget *parent) :
    QWidget(parent)
{


    // contour plot
    QHBoxLayout* layoutContour=new QHBoxLayout(this);
    setLayout(layoutContour);
    JKQTPlotter* plotContour=new JKQTPlotter(true, this);
    plotContour->setPlotUpdateEnabled(false);
    plotContour->getPlotter()->setPlotLabel(tr("\\textbf{hist contour plot}"));
    plotContour->setObjectName("contour");
    plotContour->getPlotter()->setUserSettigsFilename(QApplication::applicationDirPath()+"/usersettings.ini", "contour/");
    layoutContour->addWidget(plotContour);

    JKQTPlotter* plotDensity=new JKQTPlotter(true, this);
    plotContour->setPlotUpdateEnabled(false);
    plotContour->getPlotter()->setPlotLabel(tr("\\textbf{2D histogram plot with contours}"));
    plotDensity->getPlotter()->setPlotLabel(tr("\\textbf{2D histogram}"));
    plotContour->setObjectName("density");
    plotContour->getPlotter()->setUserSettigsFilename(QApplication::applicationDirPath()+"/usersettings.ini", "density/");
    layoutContour->addWidget(plotDensity);

    QVector<double> histAlex;
    uint histAlexNx,histAlexNy;

    // choose the test data
    histAlex.clear();
    histAlex.resize(5);
    histAlex.append(15.0);
    histAlex.append(5);
    histAlex.append(0);
    histAlex.append(0);
    histAlex.append(5);
    histAlex.append(15);
    histAlex.append(6);
    histAlex.append(6);
    histAlex.resize(16);

    histAlexNx=(uint)sqrt(histAlex.size());
    histAlexNy=histAlexNx;

    auto ds=plotDensity->getPlotter()->getDatastore();
    plotContour->getPlotter()->useExternalDatastore(ds);
    // empty datastore and grid
    plotDensity->getPlotter()->clearGraphs(true);
    ds->clear();
    plotDensity->setGrid(false);
    plotDensity->getPlotter()->getXAxis()->setAxisLabel("X");
    plotDensity->getPlotter()->getYAxis()->setAxisLabel("Y");

    size_t colHist2D=ds->addCopiedImageAsColumn(histAlex.data(), histAlexNx, histAlexNy, tr("2Dhist"));
//    size_t colContour=plotContour->getDatastore()->addCopiedImageAsColumnTranspose(histAlex.data(), histAlexNx, histAlexNy, tr("2Dhist"));

    JKQTPColumnMathImage* densityplot=new JKQTPColumnMathImage(plotDensity->getPlotter());
    densityplot->set_x(-0.1);
    densityplot->set_y(-0.1);
    densityplot->set_width(1.1);
    densityplot->set_height(1.1);
    densityplot->set_Nx(histAlexNx);
    densityplot->set_Ny(histAlexNy);
    densityplot->set_palette(JKQTPMathImageINVERTED_OCEAN);
    densityplot->set_imageColumn(colHist2D);
    densityplot->set_infColor(Qt::transparent);
    densityplot->set_nanColor(Qt::transparent);
    densityplot->set_title("density plot");
    plotDensity->addGraph(densityplot);

    densityplot=new JKQTPColumnMathImage(plotContour->getPlotter());
    densityplot->set_x(-0.1);
    densityplot->set_y(-0.1);
    densityplot->set_width(1.1);
    densityplot->set_height(1.1);
    densityplot->set_Nx(histAlexNx);
    densityplot->set_Ny(histAlexNy);
    densityplot->set_palette(JKQTPMathImageINVERTED_OCEAN);
    densityplot->set_imageColumn(colHist2D);
    densityplot->set_title("density plot");
    plotContour->addGraph(densityplot);
    plotContour->setGrid(false);
    plotDensity->zoom(-0.1,1.1,-0.1,1.1);

    QList<double> levels;
//    levels<<5<<10<<25; //    levels<<5.1<<10.1;
    levels<<4<<5<<9<<14;
    JKQTPContour* cp=new JKQTPContour(plotContour->getPlotter());
    cp->set_x(-0.1);
    cp->set_y(-0.1);
    cp->set_width(1.1);
    cp->set_height(1.1);
    cp->set_Nx(histAlexNx);
    cp->set_Ny(histAlexNy);
    cp->set_imageColumn(colHist2D);
//    cp->set_palette(JKQTPMathImageINVERTED_OCEAN);
    cp->set_contourLevels(levels);
    cp->set_title("contour plot");
    plotContour->addGraph(cp);
    plotContour->zoom(-0.1,1.1,-0.1,1.1);

    plotContour->setPlotUpdateEnabled(true);
    plotContour->redrawPlot();








}

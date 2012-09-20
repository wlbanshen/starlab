#include "geodistance.h"
#include "StarlabDrawArea.h"
#include "GeoDrawObjects.h"

void geodistance::initParameters(RichParameterSet *pars)
{
    pars->addParam(new RichInt("sourceVertex", 0, "Source vertex"));
    pars->addParam(new RichBool("visualizeDistance", true, "Visualize Distance"));

    h = NULL;
}

void geodistance::precompute()
{
    h   = new GeoHeatHelper( mesh() );
    A   = h->A();
    t   = h->t();
    Lc  = h->Lc();

    heat_flow.compute( A + (t * Lc) );
    poisson_solver.compute( Lc );
}

void geodistance::applyFilter(RichParameterSet *pars)
{
    QVector<Vertex> src(1,Vertex(pars->getInt("sourceVertex")));

    ScalarVertexProperty distance = uniformDistance(src);

    // Visualize distance on vertices
    if( pars->getBool("visualizeDistance") )
    {
        PointSoup * ps = new PointSoup;
        Vector3VertexProperty points = h->getVector3VertexProperty(VPOINT);

        foreach(Vertex v, mesh()->vertices())
            ps->addPoint( points[v], qtJetColorMap(1.0 - distance[v]) );

        drawArea()->deleteAllRenderObjects();
        drawArea()->addRenderObject(ps);
    }
}

ScalarVertexProperty geodistance::uniformDistance(const QVector<Vertex> & source)
{
    if(!h) precompute();

    // 0) Set source vertices
    u0 = h->u0( source );

    // 1) Compute heat flow for time 't'
    h->set( heat_flow.solve( u0 ), "v:heat" );

    // 2) Evaluate vector field X
    h->gradientFaces();

    // 3) Comptue distance function (solve Poisson equation)
    VectorXd d = h->divergenceVertices();
    h->set( poisson_solver.solve( d ), "v:heat_distance");

    return h->unifromDistance();
}

Q_EXPORT_PLUGIN(geodistance)

#include "swipl_cimg.h"

#include "CImg.h"
using namespace cimg_library;

#include "SWI-cpp.h"

#include <vector>
using namespace std;

SwiPl_CImg::SwiPl_CImg()
{

}

typedef CImg<unsigned char> tImg;
typedef CImgDisplay tImgDisplay;

typedef PlTerm T;
typedef PlTermv V;
typedef PlCompound C;
typedef PlTail L;

/** get back an object passed by pointer to Prolog */
template<typename Obj> Obj* pq_cast(T ptr) { return static_cast<Obj*>(static_cast<void*>(ptr)); }

#define ptrcast(Ty, Fun) inline Ty *Fun(T X) {  \
    if (Ty *p = pq_cast<Ty>(X)) return p;       \
    throw PlException("null ptr " #Ty);         \
}

// back to c++
ptrcast(tImg, TImg)
ptrcast(tImgDisplay, TImgDisplay)

// CImg constructors and methods
PREDICATE(cImg,2) {
    auto x = new tImg((const char*)PL_A1);
    PL_A2 = x;
    return TRUE;
}
PREDICATE(cImg,6) {
    int size_x = PL_A1;
    int size_y = PL_A2;
    int size_z = PL_A3;
    int size_c = PL_A4;
    int value = PL_A5;
    PL_A6 = new tImg(size_x, size_y, size_z, size_c, value);
    return TRUE;
}
PREDICATE(cImg_free,1) {
    auto i = TImg(PL_A1);
    delete i;
    return TRUE;
}
PREDICATE(blur,2) {
    auto pImg = TImg(PL_A1);
    double b = PL_A2;
    pImg->blur(b);
    return TRUE;
}
vector<int> deco_list(PlTerm t) {
    PlTail q(t);
    PlTerm v;
    vector<int> r;
    while (q.next(v))
        r.push_back(v);
    return r;
}
PREDICATE(get_crop,3) {
    auto pImg = TImg(PL_A1);
    auto ac = deco_list(PL_A2);
    if (ac.size() == 8) {
        auto pCrop = new tImg(pImg->get_crop(ac[0],ac[1],ac[2],ac[3],ac[4],ac[5],ac[6],ac[7]));
        PL_A3 = pCrop;
        return TRUE;
    }
    return FALSE;
}
PREDICATE(width,2) {
    auto pImg = TImg(PL_A1);
    return PL_A2 = pImg->width();
}
PREDICATE(fill,2) {
    auto pImg = TImg(PL_A1);
    int fill_value = (int)PL_A2;
    pImg->fill(fill_value);
    return TRUE;
}

PREDICATE(draw_graph,8) {
    auto pImg = TImg(PL_A1);
    auto pCrop = TImg(PL_A2);
    auto color = deco_list(PL_A3);
    if (color.size() == 3) {
        double opacity = PL_A4;
        int plot_type = PL_A5;
        int vertex_type = PL_A6;
        double ymin = PL_A7;
        double ymax = PL_A8;
        pImg->draw_graph(*pCrop, color.data(), opacity, plot_type, vertex_type, ymin, ymax);
        return TRUE;
    }
    return FALSE;
}
PREDICATE(display,2) {
    auto pImg = TImg(PL_A1);
    auto pDisp = TImgDisplay(PL_A2);
    pImg->display(*pDisp);
    return TRUE;
}

// CImgDisplay constructors and methods
PREDICATE(cImgDisplay,3) {
    auto pImg = TImg(PL_A1);
    const char *title = PL_A2;
    PL_A3 = new tImgDisplay(*pImg, title);
    return TRUE;
}
PREDICATE(is_closed,1) {
    auto pImgDisplay = TImgDisplay(PL_A1);
    return pImgDisplay->is_closed();
}
PREDICATE(wait,1) {
    auto pImgDisplay = TImgDisplay(PL_A1);
    pImgDisplay->wait();
    return TRUE;
}
PREDICATE(button,2) {
    auto pImgDisplay = TImgDisplay(PL_A1);
    // let unification works...
    return PL_A2 = static_cast<int>(pImgDisplay->button());
}
PREDICATE(mouse_x,2) {
    auto pImgDisplay = TImgDisplay(PL_A1);
    return PL_A2 = static_cast<int>(pImgDisplay->mouse_x());
}
PREDICATE(mouse_y,2) {
    auto pImgDisplay = TImgDisplay(PL_A1);
    return PL_A2 = static_cast<int>(pImgDisplay->mouse_y());
}

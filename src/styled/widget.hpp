#ifndef STYLED_WIDGET_INCLUDED
#define STYLED_WIDGET_INCLUDED

#include "FL/Fl_Widget.H"

#include <memory>
#include <functional>

#include <iostream>

namespace styled {

template<class W>
struct Widget: public W {

  const int id;

  inline static int nextId = 0;

  std::function<void(Fl_Widget*)> cb;

  template <typename... Args>
  Widget(const Args ...args): W(args...), id(nextId++) { }

  void operator()(std::function<void()> cb) {
    this->callback([](Fl_Widget* widget, void* data) {

      const auto callback = static_cast<std::function<void()>* >(data);

      (*callback)();

    }, &cb);
  }

  void operator()(std::function<void(Fl_Widget*)> cb) {

    this->cb = cb;

    this->callback([](Fl_Widget* widget, void* data) {

      static_cast<styled::Widget<W>*>(widget)->cb(widget);

    });
  }

};

} //namespace styled

#endif

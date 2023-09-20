#include "FL/Fl.H"
#include "FL/Fl_Widget.H"
#include "FL/Fl_Window.H"
#include "FL/Fl_Button.H"

#include "styled/widget.hpp"
#include "styled/responsive_scroll.hpp"

#include <memory>
#include <iostream>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(300,180);

  auto group = new styled::ResponsiveScroll(0, 0, 300, 180);

  group->xsep = 10;
  group->ysep = 10;

  group->begin();


  for(unsigned int i = 0; i < 20; i++){

    std::string label = "click me " + std::to_string(i);

    auto button = new styled::Widget<Fl_Button>(10, 10, 100, 100);

    button->copy_label(label.c_str());

    (*button)([i](const Fl_Widget* w) {

      std::cout << "You clicked me(" << i << ")" << std::endl;
    });
  }

  //{

  //  auto button = new styled::Widget<Fl_Button>(10, 10, 100, 100, "click me 1");

  //  (*button)([]() {
  //    std::cout << "You clicked me(" << 1 << ")" << std::endl;
  //  });

  //}

  //{
  //  auto button = new styled::Widget<Fl_Button>(10, 10, 100, 100, "click me 2");

  //  (*button)([]() {
  //    std::cout << "You clicked me(" << 2 << ")" << std::endl;
  //  });

  //}


  group->end();

  window->end();

  window->resizable(group);
  window->show(argc, argv);
  return Fl::run();
}

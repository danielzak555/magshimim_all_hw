#include "Canvas.h"


Canvas::Canvas()
{
#ifdef _WIN32

	_board = new cimg_library::CImg<unsigned char>(700, 700, 1, 3, 1);
	_disp = new cimg_library::CImgDisplay(*_board, "Super Paint");
#endif
}

Canvas::~Canvas()
{
#ifdef _WIN32
	_disp->close();
	delete _board;
	delete _disp;
#endif

}

void Canvas::draw_circle(const Point & center, double radius, Color color) const
{
#ifdef _WIN32
	_board->draw_circle(center.getX(), center.getY(), radius, get_color(color).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::draw_arrow(const Point & first_point, const Point & second_point, Color color) const
{
#ifdef _WIN32
	_board->draw_arrow(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(), get_color(color).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::draw_rectangle(const Point & first_point, const Point & second_point, Color color) const
{
#ifdef _WIN32
	_board->draw_rectangle(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(), get_color(color).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::draw_triangle(const Point & first_point, const Point & second_point, const Point & third_point, Color color) const
{
#ifdef _WIN32
	_board->draw_triangle(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(),
		third_point.getX(), third_point.getY(), get_color(color).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::clear_circle(const Point & center, double radius) const
{
#ifdef _WIN32
	unsigned char BLACK[] = { 0, 0, 0 };
	_board->draw_circle(center.getX(), center.getY(), radius, get_color(Color::black).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::clear_arrow(const Point & first_point, const Point & second_point) const
{
#ifdef _WIN32
	_board->draw_arrow(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(), get_color(Color::black).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::clear_rectangle(const Point & first_point, const Point & second_point) const
{
#ifdef _WIN32
	_board->draw_rectangle(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(), get_color(Color::black).data(), 100.0f).display(*_disp);
#endif

}

void Canvas::clear_triangle(const Point & first_point, const Point & second_point, const Point & third_point) const
{
#ifdef _WIN32
	_board->draw_triangle(first_point.getX(), first_point.getY(),
		second_point.getX(), second_point.getY(),
		third_point.getX(), third_point.getY(), get_color(Color::black).data(), 100.0f).display(*_disp);
#endif

}

std::vector<unsigned char> Canvas::get_color(Color color) const
{
	switch (color)
	{
	case Color::red:
		return std::vector<unsigned char>{ 255, 0, 0  };
	case Color::blue:
		return std::vector<unsigned char>{ 0, 0, 255  };
	case Color::green:
		return std::vector<unsigned char>{  0, 255, 0  };
	case Color::white:
		return std::vector<unsigned char>{ 255, 255, 255 };
	case Color::black:
		return std::vector<unsigned char>{ 0, 0, 0 };
	default:
		return std::vector<unsigned char>{ 0, 0, 0 };
	}
}

#pragma once

#include <list>

struct UIRect
{
	int x, y;
	int w, h;
};

class UIElement
{
public:
	UIElement(UIRect& rect) :
		_rect(rect)
	{}

	virtual void Draw(SDL_Renderer* canvas) const = 0;

protected:
	UIRect _rect;
};

class UIContainer : public UIElement
{
public:
	//UIContainer()
	//{

	//}

	inline void Add(const UIElement* element)
	{
		_children.push_back(element);
	}

	void Draw(SDL_Renderer* canvas) const
	{
		for (const UIElement* element : _children)
		{
			element->Draw(canvas);
		}
	}

private:
	std::list<const UIElement*> _children;
};

template <typename TValue>
class UVProgress : public UIElement
{
public:
	UVProgress(UIRect& rect, TValue min, TValue max, TValue threshold, TValue value = 0) :
		UIElement(rect), _min(min), _max(max), _threshold(threshold), _value(value)
	{ }

	inline TValue Get()
	{
		return _value;
	}

	inline void Set(TValue value)
	{
		_value = value;
	}

	void Draw(SDL_Renderer* canvas) const
	{
		SDL_SetRenderDrawColor(canvas, 24, 24, 24, 0);

		SDL_RenderFillRect(canvas, (SDL_Rect*)&_rect);

		auto origin_x = _rect.x;
		auto origin_y = _rect.y;

		auto origin_threshold = map(_threshold, _min, _max, origin_x, origin_x + _rect.w);
		auto origin_max = map(_value, _min, _max, origin_x, origin_x + _rect.w);

		for (int i = origin_x; i < origin_max; i += 3)
		{
			if (i > origin_threshold)
			{
				SDL_SetRenderDrawColor(canvas, 255, 0, 0, 0);
			}
			else
			{
				SDL_SetRenderDrawColor(canvas, 15, 185, 79, 0);
			}


			SDL_RenderDrawLine(canvas, i, origin_y, i, origin_y + _rect.h - 1);
		}
	}

	inline static int map(TValue x, TValue in_min, TValue in_max, int out_min, int out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	//virtual ~UVProgress() = 0;

private:
	TValue _value;
	TValue _max;
	TValue _min;

	TValue _threshold;
};
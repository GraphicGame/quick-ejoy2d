#ifndef __UIDISPLAYOBJECT
#define __UIDISPLAYOBJECT

#include <string>

namespace ui {
	class UIDisplayObject {
	public:
		UIDisplayObject();
		virtual ~UIDisplayObject();
	public:
		const std::string& getName() const;
		void setName(std::string name);
		void setName(const char *name);

		const UIDisplayObject * getParent() const;
		virtual void setParent(UIDisplayObject *parent);

		virtual void draw();

		float getX() const;
		void setX(float x);

		float getY() const;
		void setY(float y);

		float getScale() const;
		void setScale(float scale);

		float getRotation() const;
		void setRotation(float rotation);
	protected:
		std::string _name;
		UIDisplayObject *_parent;
		float _x;
		float _y;
		float _scale;
		float _rotation;
	};
}

#endif
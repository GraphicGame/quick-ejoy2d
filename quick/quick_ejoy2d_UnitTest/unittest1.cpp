#include "stdafx.h"
#include "CppUnitTest.h"
#include "../engine/events/EventDispatcher.h"
#include "../engine/geom/Point.h"
#include "../engine/geom/Rectangle.h"
#include "../engine/display/DisplayObjectContainer.h"

#include <math.h>
#include <vector>
using std::vector;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace quick::events;
using namespace quick::geom;
using namespace quick::display;

namespace quick_ejoy2d_UnitTest {		
	TEST_CLASS(UnitTest1) {
	public:
		TEST_METHOD(T_EventDispatcher) {
			
			EventDispatcher ed;
			Function *callBack = new Function();
			
			ed.addEventListener("click", callBack);
			
			Assert::AreEqual(ed.hasEventListener("click"), true);
			
			Assert::AreEqual(ed.getEventListenerCount("click"), 1);

			//udp.removeEventListener("click");
			//Assert::AreEqual(udp.getEventListenerCount("click"), 0);
			
			//udp.removeAllEventListener();
			//Assert::AreEqual(udp.getEventListenerCount("click"), 0);

			ed.removeEventListener("click", callBack);
			Assert::AreEqual(ed.getEventListenerCount("click"), 0);
		
			ed.addEventListener("click", callBack);
			
			Event *evt = new Event("click");
			ed.dispatchEvent(evt);
			Assert::AreEqual(callBack->hasCalled(), true);
		}

		TEST_METHOD(T_Point) {
			Point p;
			p.setX(2.0f);
			p.setY(3.0f);
			Assert::AreEqual(p.getX(), 2.0f);
			Assert::AreEqual(p.getY(), 3.0f);
			float x = p.getX();
			float y = p.getY();
			Assert::AreEqual(p.getLength(), sqrtf(x * x + y * y));
		}

		TEST_METHOD(T_DisplayObjectContainer) {
			DisplayObjectContainer doc;

			//0. setTouchChildren.
			doc.setChildrenTouchEnabled(false);
			Assert::AreEqual(doc.getChildrenTouchEnabled(), false);

			//1. addChild getChildrenCount
			int childCount = 10;
			for (int i = 0; i < childCount; i++) {
				DisplayObject *obj = new DisplayObject();
				doc.addChild(obj);
			}
			Assert::AreEqual(doc.getChildrenCount(), childCount);

			//2. removeChild getChildrenCount getChildAt
			vector<DisplayObject*> vec;
			for (int i = 0; i < doc.getChildrenCount(); i++) {
				vec.push_back(doc.getChildAt(i));
			}
			for (int i = 0; i < vec.size(); i++) {
				doc.removeChild(vec[i]);
			}
			Assert::AreEqual(doc.getChildrenCount(), 0);

			//3. addChildAt getChildrenCount
			childCount = 10;
			for (int i = 0; i < childCount; i++) {
				DisplayObject *obj = new DisplayObject();
				doc.addChildAt(obj, i);
			}
			Assert::AreEqual(doc.getChildrenCount(), childCount);

			//4. addChildAt getChildAt
			{
				DisplayObject *objTemp = new DisplayObject();
				objTemp->setName("objTemp");
				doc.addChildAt(objTemp, 2);
				Assert::AreEqual(doc.getChildAt(2)->getName().c_str(), "objTemp");
			}
			//5. setChildIndex getChildAt
			{
				DisplayObject *obj = doc.getChildAt(6);
				obj->setName("66child");
				doc.setChildIndex(obj, 2);
				Assert::AreEqual(doc.getChildAt(2)->getName().c_str(), "66child");
			}
			//6. swapChildren
			{
				DisplayObject *obj1 = doc.getChildAt(2);
				DisplayObject *obj2 = doc.getChildAt(8);
				obj1->setName("2222");
				obj2->setName("8888");
				doc.swapChildren(obj1, obj2);
				Assert::AreEqual(doc.getChildAt(8)->getName().c_str(), "2222");
				Assert::AreEqual(doc.getChildAt(2)->getName().c_str(), "8888");
			}
		}

		TEST_METHOD(T_Rectangle) {
			Rectangle rect(0, 0, 100, 100);
			Assert::AreEqual(rect.getX(), 0.0f);
			Assert::AreEqual(rect.getY(), 0.0f);
			Assert::AreEqual(rect.getWidth(), 100.0f);
			Assert::AreEqual(rect.getHeight(), 100.0f);

			Rectangle rectCopy(rect);
			Assert::AreEqual(rectCopy == rect, true);
			Rectangle rectClone = rect.clone();
			Assert::AreEqual(rectClone == rect, true);
			rectClone.setX(23);
			Assert::AreEqual(rectClone == rect, false);

			Assert::AreEqual(rect.contains(1, 1), true);
			Assert::AreEqual(rect.contains(1, 101), false);

			rect.setEmpty();
			Assert::AreEqual(rect.getX(), 0.0f);
			Assert::AreEqual(rect.getY(), 0.0f);
			Assert::AreEqual(rect.getWidth(), 0.0f);
			Assert::AreEqual(rect.getHeight(), 0.0f);
		}
	};
}
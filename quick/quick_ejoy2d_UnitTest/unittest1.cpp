#include "stdafx.h"
#include "CppUnitTest.h"
#include "../engine/events/EventDispatcher.h"
#include "../engine/geom/Point.h"

#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace quick::events;
using namespace quick::geom;

namespace quick_ejoy2d_UnitTest {		
	TEST_CLASS(UnitTest1) {
	public:
		TEST_METHOD(TestEventDispatcher) {
			Logger::WriteMessage("test EventDispatcher...");
			
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

		TEST_METHOD(TestPoint) {
			Point p;
			p.setX(2.0f);
			p.setY(3.0f);
			Assert::AreEqual(p.getX(), 2.0f);
			Assert::AreEqual(p.getY(), 3.0f);
			float x = p.getX();
			float y = p.getY();
			Assert::AreEqual(p.getLength(), sqrtf(x * x + y * y));
		}
	};
}
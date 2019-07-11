#include <EventEmitter.h>

class Test {
public:
  static int add(int x, int y) { return x + y; }
};

Test t;

struct point {
  point (int x, int y) : x(x), y(y) {}
  float x;
  float y;
};

int a = 1;
int b = 2;

EventEmitter<int, int> e1;
EventEmitter<> e2;
EventEmitter<point> e3;

void setup() {
  Serial.begin(9600);

  e1.addListener("sum", [](int a, int b) { Serial.println(a + b); });

  e2.addListener("yep", []() { Serial.println("yop !"); });
  e2.addListener("yep", []() { Serial.println("yup ?"); });

  // we must catch the context here (&) to access global variables (t) :
  e3.addListener("coucou", [&](point p) { Serial.println(t.add(a, p.x)); });
}

void loop() {
  e1.emit("sum", 1, 2);
  e2.emit("yep");
  e3.emit("coucou", point(23, 24));
  delay(1000);

  if (millis() > 10000) {
    e2.removeListeners("yep");
  }
}
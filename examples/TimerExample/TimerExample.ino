#include <EventEmitter.h>

class Timer : public EventEmitter<unsigned long> {
private:
  unsigned long period;
  unsigned long lastTickDate;

public:
  Timer(unsigned long p) : EventEmitter<unsigned long>(),
  period(p), lastTickDate(0) {}

  ~Timer() {}

  void setPeriod(unsigned long p) { period = p; }

  void update() {
    unsigned long now = millis();
    
    if (now - lastTickDate >= period) {
      lastTickDate = now;
      emit("tick", now);
    }
  }
};

Timer timer(2000);

void setup() {
  Serial.begin(9600);

  timer.addListener("tick", [](unsigned long date) {
    Serial.print("new tick event emitted at ");
    Serial.print(date * 0.001, 3); // display 3 decimals
    Serial.println(" seconds");
  });
}

void loop() {
  timer.update();
  delay(10);
}
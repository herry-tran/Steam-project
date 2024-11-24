  #include <PS2X_lib.h>  // Thư viện để điều khiển tay cầm PS2
  #include <Servo.h>     // Thư viện để điều khiển servo

  // Chân kết nối giữa tay cầm PS2 và Arduino
  #define PS2_DAT 12  
  #define PS2_CMD 11  
  #define PS2_SEL 10  
  #define PS2_CLK 13  

  PS2X ps2x;  // Tạo một đối tượng PS2X
  Servo myservo1;  // Tạo một đối tượng Servo cho servo thứ nhất
  Servo myservo2;  // Tạo một đối tượng Servo cho servo thứ hai

  // Chân điều khiển module L298N cho động cơ A
  #define ENA 3  // Chân PWM cho động cơ A - 
  #define IN1 8  // Chân điều khiển hướng 1 cho động cơ A
  #define IN2 7  // Chân điều khiển hướng 2 cho động cơ A

  // Chân điều khiển module L298N cho động cơ B
  #define ENB 9  // Chân PWM cho động cơ B
  #define IN3 2  // Chân điều khiển hướng 1 cho động cơ B
  #define IN4 4  // Chân điều khiển hướng 2 cho động cơ B

  // Chân điều khiển servo
  #define SERVO_PIN1 5  // Chân điều khiển servo thứ nhất
  #define SERVO_PIN2 6  // Chân điều khiển servo thứ hai

  // Chân điều khiển bằng nút L1
  #define L1_PIN A0  // Chân điều khiển cho nút L1

  void setup() {
    Serial.begin(9600);  // khởi tạo giá trị giao tiếp Serial với tốc độ 9600 để in thông báo
    
    // Thiết lập kết nối với tay cầm PS2
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
    
    if(error == 0){
      Serial.println("Found Controller, configured successful");
    }  
    else if(error == 1){
      Serial.println("No controller found, check wiring");
    }
    else if(error == 2){
      Serial.println("Controller found but not accepting commands");
    }
    else if(error == 3){
      Serial.println("Controller refusing to enter Pressures mode, may not support it");
    }

    // Thiết lập các chân điều khiển động cơ
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Thiết lập chân điều khiển servo
    myservo1.attach(SERVO_PIN1);
    myservo2.attach(SERVO_PIN2);
    
    myservo1.write(100);
    myservo2.write(25);
    
    // Thiết lập chân điều khiển cho nút L1
    pinMode(L1_PIN, OUTPUT);
    digitalWrite(L1_PIN,HIGH);
  }

  void loop() {
    // Giá trị trục Y dao động từ 0 => 255, khi giá trị = 0 thì joystick đẩy lên hoàn toàn
      // còn gtri trục Y là 255 thigf joystik đẩy xg hoàn toàn  =>> giá trị là 128 thì giá trị tb => ko dịch chuyển
    // Đọc trạng thái từ tay cầm PS2
    ps2x.read_gamepad(false, 0); // cho biết trạng thái cần đọc dữ liệu từ tay cầm , còn 0 là ko delay khi đọc dữ liệu
                                

    // Lấy giá trị từ joystick trái
    int joystickLeftY = ps2x.Analog(PSS_LY); // Giá trị trục Y của joystick trái

    // Lấy giá trị từ joystick phải
    int joystickRightY = ps2x.Analog(PSS_RY); // Giá trị trục Y của joystick phải

    // Tốc độ động cơ
    int motorSpeed = 255; // Đặt tốc độ động cơ cố định là 255

    // Điều khiển động cơ A dựa trên giá trị từ joystick trái
    if (joystickLeftY < 100) {
      // Joystick trái đẩy lên -> động cơ A quay thuận với tốc độ đã thiết lập
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, motorSpeed); // Sử dụng tốc độ đã thiết lập
    } else if (joystickLeftY > 150) {
      // Joystick trái đẩy xuống -> động cơ A quay ngược với tốc độ đã thiết lập
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, motorSpeed); // Sử dụng tốc độ đã thiết lập
    } else {
      // Joystick trái ở vị trí trung gian -> động cơ A dừng
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }

    // Điều khiển động cơ B dựa trên giá trị từ joystick phải
    if (joystickRightY < 100) {
      // Joystick phải đẩy lên -> động cơ B quay thuận với tốc độ đã thiết lập
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, motorSpeed); // Sử dụng tốc độ đã thiết lập
    } else if (joystickRightY > 150) {
      // Joystick phải đẩy xuống -> động cơ B quay ngược với tốc độ đã thiết lập
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, motorSpeed); // Sử dụng tốc độ đã thiết lập
    } else {
      // Joystick phải ở vị trí trung gian -> động cơ B dừng
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);
    }
    
    // Kiểm tra xem nút tam giác có được nhấn hay không
    if (ps2x.Button(PSB_TRIANGLE)) {
      myservo1.write(160); // Di chuyển servo thứ nhất tới góc 160 độ
    }

    // Kiểm tra xem nút X có được nhấn hay không
    if (ps2x.Button(PSB_CROSS)) {
      myservo1.write(18); // Di chuyển servo thứ nhất tới góc 18 độ
    }

    // Kiểm tra xem nút vuông có được nhấn hay không
    if (ps2x.Button(PSB_SQUARE)) {
      myservo2.write(7); // Di chuyển servo thứ hai tới góc 19 độ
    }

    // Kiểm tra xem nút tròn có được nhấn hay không
    if (ps2x.Button(PSB_CIRCLE)) {
      myservo2.write(47); // Di chuyển servo thứ hai tới góc 47 độ
    }

    // Kiểm tra xem nút L1 có được nhấn hay không
    if (ps2x.Button(PSB_L1)) {
      digitalWrite(L1_PIN, LOW);
      delay(10);
      digitalWrite(L1_PIN, HIGH);
      delay(10);
    }

    delay(25); // Độ trễ để ổn định
  }

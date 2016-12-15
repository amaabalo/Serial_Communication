import processing.serial.*;
Serial myPort;

float theta;
void setup()
{
  size(600,600);
  String portName = "/dev/tty.usbserial-DN01EZ6S";
  myPort = new Serial(this, portName, 9600);
}

void draw()
{ 
  background(0);
}

void mouseReleased()
{
  byte x;
  theta = atan2(mouseY-height/2, mouseX-width/2);
  if (theta < 0)
  {
    theta += 2*PI;
  }
  x = byte(theta/(PI/3));
  myPort.write(x);
  println(x);
}
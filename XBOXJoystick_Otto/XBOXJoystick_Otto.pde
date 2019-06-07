/**
 Basic demonstration of using a joystick.
 
 When this sketch runs it will try and find
 a game device that matches the configuration
 file 'joystick' if it can't match this device
 then it will present you with a list of devices
 you might try and use.
 
 The chosen device requires 2 sliders and 2 buttons.
 */

import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;

ControlIO control;
ControlDevice stick;
float px, py, pa, pb;
boolean trailOn;

ArrayList<PVector>  shadows = new ArrayList<PVector>();
ArrayList<PVector>  trail = new ArrayList<PVector>();

import hypermedia.net.*;

UDP udp; // define the UDP object

String ip = "192.168.1.28"; // the remote IP address
int port = 8888; // the destination port

byte command[] = {90,90,90,90};

public void setup() {
  size(400, 400);
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  stick = control.getMatchedDevice("joystick");
  if (stick == null) {
    println("No suitable device configured");
    System.exit(-1); // End the program NOW!
  }
  // Setup a function to trap events for this button
  stick.getButton("SHADOW").plug(this, "dropShadow", ControlIO.ON_RELEASE);
}

// Poll for user input called from the draw() method.
public void getUserInput() {
  px = map(stick.getSlider("X").getValue(), -1, 1, 0, width);
  py = map(stick.getSlider("Y").getValue(), -1, 1, 0, height);
  pa = map(stick.getSlider("A").getValue(), -1, 1, 0, width);
  pb = map(stick.getSlider("B").getValue(), -1, 1, 0, height);  
  trailOn = stick.getButton("TRAIL").pressed();
}

// Event handler for the SHADOW button
public void dropShadow() {
  // Make sure we have the latest position
  getUserInput();
  shadows.add(new PVector(px, py, 40));
}

void sendcommand(int leftJoyX, int leftJoyY, int rightJoyX, int rightJoyY) {
  //compile the command from its words
  command[0] = byte(map(leftJoyX, 0, 1024, 0, 180));
  command[1] = byte(map(leftJoyY, 0, 1024, 0, 180));
  command[2] = byte(map(rightJoyX, 0, 1024, 0, 180));
  command[3] = byte(map(rightJoyY, 0, 1024, 0, 180));
  udp.send(command, ip, port);  
  print(command);
}

public void draw() {
  getUserInput(); // Polling
  background(255, 255, 240);
  // Show position
  noStroke();
  fill(255, 64, 64, 64);
  ellipse(px, py, 20, 20);
  sendcommand(int(px), int(py), int(pa) , int(pb));
}
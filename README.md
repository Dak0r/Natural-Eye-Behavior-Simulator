# Natural-Eye-Behavior-Simulator
A simple implementation for simulating natural eye movement (there's no UI, just data)


## Example usage:

```C
  EyeConfig eyeconfig; // default config
  Eye eye();
  
  unsigned long time_now =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  
  // Setup eye with default config and set uo inital values.
  // last parameter causes the eye to generate a default list of eye modifiers (random look and random blink)
  eye.init(time_now, &eyeconfig, nullptr);  
  
  while(!abort){
    // we need a timestamp in milliseconds, the library works with relative values, so it's not important if it's realtime or time since application start etc.
    unsigned long time_now =  duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
    // updates eye behavior which calculates natural, random eye movements
    eye.update(time_now); 
    
    // get current values
    float posX = eye.get_position_x();
    float posY = eye.get_position_y();
    float eyelid_upper_pos = eye.get_upper_eyelid();
    float eyelid_lower_pos = eye.get_lower_eyelid();
    float eyelid_lower_pos = eye.get_lower_eyelid();
    float pupil_size = eye.get_pupil_size()
    
    // call your render function
    renderEye(posX, posY, eyelid_upper_pos, eyelid_lower_pos, pupil_size);
  }
```

See my Cyborg Eye Arduino Sketch for an more complete example: https://github.com/Dak0r/Cyborg-1.5-Oled-Eye-Arduino/blob/master/Cyborg-1.5-Oled-Eye.ino

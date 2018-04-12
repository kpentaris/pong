//
// @author kpentaris - 12/4/2018.
//

#include <stdbool.h>
#include "MathUtils.h"

short find_symmetrical_angle(short angle, bool y_axis_symmetry) {
  short new_angle;
  if (y_axis_symmetry) {
    if (angle < 180) {
      new_angle = (short) (2 * 90 - angle);
    } else {
      new_angle = (short) (2 * 270 - angle);
    }
  } else {
    if (angle < 90 || angle > 270) {
      new_angle = (short) (2 * 360 - angle);
    } else {
      new_angle = (short) (2 * 180 - angle);
    }
  }
  if (new_angle > 360) {
    new_angle -= 360;
  } else if (new_angle < 0) {
    new_angle += 360;
  }
  return new_angle;
}
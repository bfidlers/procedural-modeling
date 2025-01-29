import math


def sine(angle):
    result = math.sin(angle * math.pi/180)
    return round(result, 8)


def cosine(angle):
    result = math.cos(angle * math.pi/180)
    return round(result, 8)


def inverse_angle(angle):
    if angle == 0:
        return 180
    elif angle > 0:
        return angle - 180
    else:
        return angle + 180


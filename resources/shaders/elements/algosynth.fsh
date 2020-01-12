#version 330 core

layout(location = 0) out vec4 color;

uniform float seconds = 0.0;

uniform float rate = 1.0;
uniform float cutoff = 0.0;

uniform float blend = 1.0;

uniform int bitshift1 = 0;
uniform int bitshift2 = 0;
uniform int bitmask = ~0;

uniform int programValues = 0;
uniform int programColors = 0;

int width  = 256;
int height = 192;

void main() {
    int row = int(floor(gl_FragCoord.y));
    int col = int(floor(gl_FragCoord.x));

    int t = row * width + col;

    int val1 = 0;
    int val2 = 0;
    int r, g, b;

    switch(programValues) {
    case 0:
        val1 = (row >> bitshift2) & (col >> bitshift1) *
            int(seconds/1000.0f*rate*(row^col));
        break;

    case 1:
        val1 = (t << bitshift2) & (col << bitshift1) *
            int(seconds/1000.0f*rate*(row^t));
        break;

    case 2:
        val1 =
            (t >>  bitshift1) &
            (t >>  bitshift2) | int(seconds*row);
        val2 = (t >> bitshift2) | (t | int(seconds*row));
        break;

    case 3:
        val1 =
            (t >>  bitshift1) &
            (t >>  bitshift2) | int(seconds*row);
        val2 = (t >> bitshift2) | (t & int(seconds*col));
        break;

    case 4:
        int i = 10;
        val1 =
            (t >>  bitshift1) +
            (t >>  bitshift2) | int(seconds*col / i);
        val2 = (t >> bitshift1) | (t & int(seconds*row / i));
        break;

    default:
        val1 =
            int(rate * t) >>  bitshift1 &
            int(rate * t / 6) >>  bitshift2 | int(seconds*col);
        val2 = int(rate * t / 7) >> bitshift1 | (t & int(seconds*row));
        break;
    }

    val1 &= 0xFF;
    val2 &= 0xFF;

    switch(programColors) {
    case 0:
        r = int(val2 * (cutoff) * (1-float(col)/width));
        g = int(val1 * (cutoff) * (float(col)/width));
        b = int(val2 * (1-cutoff));
        break;

    case 1:
        r = int(val2 * (cutoff));
        g = int(val1 * (1-cutoff));
        b = 0;
        break;

    default:
        r = int(val1 * cutoff);
        g = int(~val2 * cutoff) & bitmask;
        b = 0;
        break;
    }

    color = vec4(r / 255.0f, g / 255.0f, b / 255.0f, blend);
}

#version 330 core

layout(location = 0) out vec4 color;

uniform float seconds = 0.0;

uniform float rate = 1.0;
uniform float cutoff = 0.0;

uniform float alpha = 1.0;

uniform uint bitshift1 = 0u;
uniform uint bitshift2 = 0u;
uniform uint bitmask = ~0u;

uniform uint program_values = 0u;
uniform uint program_colors = 0u;

uint width  = 256u;
uint height = 192u;

void main() {
    uint row = uint(floor(gl_FragCoord.y));
    uint col = uint(floor(gl_FragCoord.x));

    uint t = row * width + col;

    uint val1 = 0u;
    uint val2 = 0u;
    float r, g, b;

    switch(program_values) {
    case 0u:
        val1 = (row << bitshift2) & (col << bitshift1) *
            uint(seconds/1000.0f*rate*(row^col));
        break;

    case 1u:
        val1 = (t << bitshift2) & (col << bitshift1) *
            uint(seconds/1000.0f*rate*(row^t));
    }

    switch(program_colors) {
    case 0u:
        r = val1 / 255.0f;
        g = val1 / 255.0f * (cutoff) * (col/width);
        b = val1 / 255.0f * (1-cutoff);
        break;

    case 1u:
        r = val1 / 255.0f * (1-cutoff);
        g = 0;
        b = val1 / 255.0f * (1-cutoff);
    }

    color = vec4(r, g, b, alpha);
}

        // for(int row = 0 ; row < texture->getHeight() ; ++row) {
        //     for(int col = 0 ; col < texture->getWidth() ; ++col) {
        //         // uint value = (col<<1) ^ (row+1+int(seconds()*100));
        //         // uint value2 = (row<<1) ^ (row+1+int(seconds()*120));
        //         // texData[row][3*col+0] = value2;
        //         // texData[row][3*col+1] = value;
        //         // texData[row][3*col+2] = ~value2;

        //         // uint value = (col<<1) ^ (row+1+int(seconds()*10));
        //         // uint value2 = (row<<1) ^ (row+1+int(seconds()*12));
        //         // texData[row][3*col+0] = value2;
        //         // texData[row][3*col+1] = value * value2;
        //         // texData[row][3*col+2] = ~value2;
        //         int t = row * texture->getWidth() * col;

        //         t &= bitmask;
        //         t *= rate;

        //         int a =
        //             (t >>  bitshift1) &
        //             (t >>  bitshift2) | int(seconds()*row);
        //         int b = (t >> bitshift2) | (t | int(seconds()*row));

        //         // int a =
        //         //     (t >>  bitshift1) &
        //         //     (t >>  bitshift2) | int(seconds()*row);
        //         // int b = (t >> bitshift2) | (t & int(seconds()*col));

        //         // int i = 10;
        //         // int a =
        //         //     (t >>  bitshift1) +
        //         //     (t >>  bitshift2) | int(seconds()*col / i);
        //         // int b = (t >> bitshift1) | (t & int(seconds()*row / i));

        //         // int a =
        //         //     (row >> bitshift2) & (col >> bitshift1) *
        //         //     int(seconds()*rate*(row^col));

        //         texData[row][4*col+0] = a * cutoff;
        //         texData[row][4*col+1] = b;
        //         texData[row][4*col+2] = int(~a * cutoff) & bitmask;
        //         texData[row][4*col+3] = 255;
        //     }
        // }

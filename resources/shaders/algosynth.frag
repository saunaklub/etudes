#version 330 core

layout(location = 0) out vec4 color;

uniform float seconds = 0.0;

uniform float rate = 1.0;
uniform float cutoff = 0.0;

uniform uint bitshift1 = 0u;
uniform uint bitshift2 = 0u;
uniform uint bitmask = ~0u;

void main() {
    uint row = uint(floor(gl_FragCoord.y));
    uint col = uint(floor(gl_FragCoord.x));

    uint a =
        (row << bitshift2) & (col << bitshift1) *
        uint(seconds/1000.0f*rate*(row^col));

    float r = a / 255.0f * (1-cutoff);
    float g = a / 255.0f * cutoff;
    float b = (255u-a) / 255.0f * (1-cutoff);

    color = vec4(r, g, b, 1);
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

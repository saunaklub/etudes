~order = 3;
~numberOfHarmonics = (~order + 1) * (~order + 1);

Fdef(\hoaFilter, {
    var sig;
    sig = \in.ar(0);
    sig = sig!(~numberOfHarmonics);
    sig.do{
        arg harmonic, index;
        sig[index] = BPF.ar(harmonic, \filterFreq.ar(10000) / ((~numberOfHarmonics * ~numberOfHarmonics) - (index * index) + 1), \reciproQ.ar(0.5), \filterMul.ar(1));
    };
    sig;
});

Fdef(\encoder, {
    var sig = \in.ar(0);
    sig = Encoder3D.ar(sig, ~order, \azimuth.kr(0),\elevation.kr(0), \radius.kr(1));
    sig;
});

Fdef(\hoaFlanger, {
    var sig;
    sig = \in.ar(0);
    sig = sig!(~numberOfHarmonics);
    sig.do {
        arg harmonic, index;
        if(index > 0, {
            sig[index] = DelayC.ar(harmonic, 5, \baseDelay.kr(1.0) +
            SinOsc.ar(\freq.kr(0.5), index/~numberOfHarmonics, mul:0.5 ,add:0.5) *
            \depth.kr(0.01) * index/~numberOfHarmonics, \mul.kr(1),\add.kr(0)); 
        });
    };
    sig;
});

Fdef(\hoaFlanger2, {
    var sig;
    sig = \in.ar(0);
    sig = sig!(~numberOfHarmonics);
    sig.do {
        arg harmonic, index;
        if(index > 0, {
            sig[index] = DelayC.ar(harmonic, 5, \baseDelay.kr(1.0) +
            SinOsc.ar(\freq.kr(0.5), index/~numberOfHarmonics, mul:0.5 ,add:0.5) *
            \depth.kr(0.01), \mul.kr(1),\add.kr(0)); 
        });
    };
    sig;
});

Fdef(\hoa3DDecoder, {
    var sig, out;
    sig = \in.ar(0)!(~numberOfHarmonics);
    out = Decoder3D.ar(sig, ~order, 16);
    out;
});

Fdef(\hoa3DBinaural, {
    var sig, out;
    sig = \in.ar(0)!(~numberOfHarmonics);
    out = Decoder3DBinaural.ar(sig, ~order, 256);
    out;
});

Fdef(\delay,{
    var sig = \in.ar(0)!(~numberOfHarmonics);
    sig.do{
        arg index, harmonic;
        DelayC.ar(sig)
    }
})

(
    Tdef(\oscUpdate, {
        loop{
            Ndef(\sinOsc2).bus.get({
                arg v; 
                ~etudes.sendMsg(
                    "/lines/distance/omega", v.linlin(0,1,0,2pi)
                ); 
            });
            Ndef(\sinOsc3).bus.get({
                arg v; 
                ~etudes.sendMsg(
                    "/lines/distance/amplitude", v.linlin(0,1,0.02,0) * ~midiValue[1] * 10
                ); 
            });
            Ndef(\LFSaw1).bus.get({
                arg v; 
                ~etudes.sendMsg(
                    "/lines/count", v.linlin(-100,100,100, 300)
                ); 
            });
            Ndef(\lfPulse1).bus.get({
                arg v; 
                ~etudes.sendMsg(
                    "/lines/width/amplitude", v.linlin(0,1,0,0.02)
                ); 
            });
            (1/60).wait;
        }
    });
)

(
    (0..16).do{
        arg i;
        var l, m;
        l = (i**(1/2)).floor;
        m = i - (l * (l+1));
        [l,m].postln;
    }
)

ServerOptions.devices

Ndef(\noise) <>> Ndef(\hoaFlanger);
Ndef(\hoaFlanger) <>> Ndef(\hoa3DDecoder);
Ndef(\hoaFlanger) <>> Ndef(\hoa3DBinaural);
Ndef(\hoaFilter) <>> Ndef(\hoa3DDecoder);

Ndef(\hoaFilter) <<> nil;
Ndef(\hoaFlanger) <<> nil;
Ndef(\hoa3DBinaural) <<> nil;
Ndef(\hoa3DDecoder) <<> nil;

Ndef(\hoa3DDecoder).bus.scope
Ndef(\hoa3DDecoder).play(0,16);
Ndef(\hoa3DDecoder).stop;
Ndef(\hoa3DBinaural).bus.scope;
Ndef(\hoa3DBinaural).play(0,2)
Ndef(\hoa3DBinaural).stop
Ndef(\hoaFlanger).play(0,16)
Ndef(\hoaFlanger).stop
Ndef(\hoaFlanger).bus.scope

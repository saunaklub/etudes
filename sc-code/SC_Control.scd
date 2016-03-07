(
    Tdef(\init, {

        ("Server.scd").loadRelative;

        s.bootSync;

        ("Midi.scd").loadRelative;
        s.sync;
        ("Definitions.scd").loadRelative;
        s.sync;


        Environment.push(~etudes);

        //NDEFS
        Ndef('sinOsc1', Fdef(\sinOsc)).set('freq', 0.3, 'mul', 300,'add', 35);
        s.sync;
        Ndef('sinOsc2', Fdef(\sinOsc)).set('freq', 0.1, 'mul', 0.5,'add', 0.5);
        s.sync;
        Ndef('sinOsc3', Fdef(\sinOsc)).set('freq', 0.1, 'mul', 0.5,'add', 0.5);
        s.sync;
        Ndef('lfSaw1', Fdef(\lfSaw)).set('freq', 1, 'mul', 100,'add', 0);
        s.sync;
        Ndef('lfPulse1', Fdef(\lfPulse)).set('freq', 3, 'mul', 50,'add', 100);
        s.sync;
        Ndef('noise', Fdef(\noise)).set('freq', 300, 'mul', 2,'add', -1);
        s.sync;

        // NDEF ROUTING
        Ndef('sinOsc2').map(\freq, Ndef('sinOsc1'));
        s.sync;
        Ndef('sinOsc3').map(\freq, Ndef('lfsaw'));
        s.sync;
        Ndef('lfPulse1').map(\width, Ndef('sinOsc3'));
        s.sync;
        Ndef('noise').map(\width, Ndef('sinOsc2'));
        s.sync;
        Ndef('noise').map(\freq,Ndef('lfPulse1'));
        s.sync;

        // MIDI MAP
        Ndef(\lfPulse1).map(\add, Ndef('mapper',{~midiBus[116].kr(1) * 300}));
        s.sync;
        Ndef(\lfPulse1).map(\freq, Ndef('mapper2',{~midiBus[27].kr(1) * 300}));
        s.sync;

        ~registerValue.value("/lines/angle", \sinOsc1, -265,335,0,4pi);
        ~registerValue.value("/lines/distance/omega", \sinOsc2, 0,1,0,2pi);
        ~registerValue.value("/lines/distance/base", \sinOsc3, 0,1,0.02,0);
        ~registerValue.value("/lines/count", \LFSaw1, -100,100,100, 300);
        ~registerValue.value("/lines/width/amplitude", \lfPulse2, 0,1,0,0.02);

        Tdef(\oscUpdate, {
            loop{
                ~sendValues.value();
                (1/60).wait;
            }
        });

        s.sync;

        Environment.pop;
        
        "done".postln;
    });
    Tdef(\init).play;
)
// CONTROL AREA
Tdef(\oscUpdate).play(doReset:true)
Tdef(\oscUpdate).stop

Ndef(\noise).play(0,2)
Ndef(\noise).stop

s.quit

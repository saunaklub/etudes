s.options.device = "Saffire";

(
    ~init = Task({
        ~myPath = "/Users/claudiocabral/Projetos/etudes/sc-code/";
        1.wait;
        (~myPath ++"Server.scd").load;
        1.wait;
        s.waitForBoot({
            (~myPath ++ "Midi.scd").load;
            s.wait;
            (~myPath ++"Definitions.scd").load; 
            s.wait;
            ~oscUpdate = Task({
                loop{
                    ~midiBus[116].get({arg v;~patric.sendMsg("/lines/distance/amplitude",v.linlin(0,1,0,0.02));});
                    ~midiBus[27].get({arg v;~patric.sendMsg("/lines/angle",v);});
                    0.016.wait;
                };
            });
            0.5.wait;

            //NDEFS
            Ndef('sinOsc1', ~sinOsc).set('freq', 300, 'mul', 300,'add', 35);
            0.5.wait;
            Ndef('sinOsc2', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
            0.5.wait;
            Ndef('sinOsc3', ~sinOsc).set('freq', 300, 'mul', 0.5,'add', 0.5);
            0.5.wait;
            Ndef('lfSaw1', ~lfSaw).set('freq', 1, 'mul', 100,'add', 1);
            0.5.wait;
            Ndef('lfPulse1', ~lfPulse).set('freq', 300, 'mul', 50,'add', 100);
            0.5.wait;
            Ndef('noise', ~noise).set('freq', 300, 'mul', 2,'add', -1);
            0.5.wait;

            // NDEF ROUTING
            Ndef('sinOsc2').map(\freq, Ndef('sinOsc1'));
            Ndef('sinOsc3').map(\freq, Ndef('lfsaw'));
            Ndef('lfPulse1').map(\width, Ndef('sinOsc3')); 
            Ndef('noise').map(\width, Ndef('sinOsc2'));
            Ndef('noise').map(\freq,Ndef('lfPulse1'));
            
            // MIDI MAP
            Ndef(\lfPulse1).map(\add, Ndef('mapper',{~midiBus[116].kr(1) * 300}));
            Ndef(\lfPulse1).map(\freq, Ndef('mapper2',{~midiBus[27].ar(1) * 300}));

            "done".postln;
        });
    });

    ~init.play;
)

// CONTROL AREA
~oscUpdate.play(doReset:true)
~oscUpdate.stop 

Ndef(\noise).play(0,2)
Ndef(\noise).stop

s.quit

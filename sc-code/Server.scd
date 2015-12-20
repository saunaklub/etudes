s = Server.scsynth.local;
s.options.protocol = \tcp;
s.options.hardwareBufferSize = 64;
s.options.threads = 4;

//~etudes =  NetAddr.new("192.168.0.26", 6666);
~etudes =  NetAddr.new("localhost", 6666);

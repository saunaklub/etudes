s = Server.scsynth.local;
s.options.protocol = \tcp;

~etudes = ();

Environment.push(~etudes);

//~host =  NetAddr.new("192.168.0.26", 6666);
~host =  NetAddr.new("localhost", 6666);

Environment.pop;

# Études Audiovisuel

The project provides several OpenGL-based renderers named *études*,
which serve as graphical building blocks inside a more complex
audiovisual setup. Études is french for 'study' or 'exercise', and is
commonly encountered in musical composition.

In our context, the idea is to
collect small self-contained renderers, which make use of one
particular graphical effect. They serve to study the particular
technical difficulties and stylistic properties of one creative
graphical element, and the interplay with music and sound properties
which are concertedly modulated.

### Toolchain

The following soft- and hardware components are probably used in the
overall a/v toolchain for our envisioned setup.

#### High-level arrangement

- Sequencing: [Bitwig](http://www.bitwig.com/en/bitwig-studio.html) / [Renoise](http://www.renoise.com/) / [Live](https://www.ableton.com/en/live/) / [radium](http://users.notam02.no/~kjetism/radium/index.php)
- Transport: [MIDI](http://www.midi.org/techspecs/index.php), [OSC](http://opensoundcontrol.org/), [DMX](https://en.wikipedia.org/wiki/DMX512)
- Control data generation: [IanniX](http://www.iannix.org/en/), [i-score](http://i-score.org/)
- Live input sources: Controllers, Sensors, Audio
 
#### Sound synthesis

- [SuperCollider](https://supercollider.github.io/)
- LADSPA/DSSI/VST
- Analog gear

#### Video processing

- Effects, layering, composition: [veejay](http://veejayhq.net/)
- Projection mapping: [MapMap](http://www.mapmap.info/tiki-index.php) / [lpmt](http://hv-a.com/lpmt/)

#### High-level Overview

![Etudes architectural overview](https://raw.githubusercontent.com/saunaklub/etudes/master/doc/diagrams/workflow.png)

### Development

The project is written in C++14 and OpenGL 3.3+.

#### Dependencies

- [CMake](https://cmake.org/)
- [liblo](http://liblo.sourceforge.net/)
- [glm](http://glm.g-truc.net/)

Libraries to consider

- [Jamoma](http://jamoma.org/)
- [libmapper](http://libmapper.github.io/)

#### License

All software components developed for the project are released under
terms of the GNU General Public License 3.0. The goal is to get a
complete toolchain made of free software components. The only part
which seems to be lacking right now is the sequencing
software. Suggestions for free sequencers are very welcome!

#### Team

Patric Schmitz (<flavi0@openmailbox.org>)<br>
Claudio Cabral (<cabral1349@gmail.com>)

We are based in Paris right now, but being connected over the Internet
we are happy about anyone who wants to participate. We want this
project to be as open as possible from the outset. If you are
interested in our work, want to contribute your own études into the
framework, have creative ideas, suggestions or questions about the
project, please do not hesitate to get in touch with us!

#### Contribution

Bug tracking, pull requests, and discussion about specific issues
happens on GitHub. For more general user and developer discussion and
support, please write to the **TODO** mailing list.

We don't make any fuss about a coding style rulebook. If you want to
contribute, have a look at the existing code and use some common sense
to comply with what is already there. If we feel things should be
adjusted in a particular way before merging, we will kindly ask you to
adapt your pull requests accordingly.

Happy Hacking!
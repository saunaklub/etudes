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

### Architecture

Here a description of the inner architecture of the études modules is
given, as well as a sketch of the overall processing toolchain and the
other software / hardware components involved in our envisioned setup.

#### High-level arrangement

- Sequencing: Bitwig, Renoise, Live
- Transport: MIDI / OSC
- Control data generation: IanniX, i-score
- Live input sources: Controllers, Sensors, Audio
 
#### Sound synthesis

- SuperCollider
- LADSPA/DSSI/VST
- Analog gear

#### Video processing

- Effects, layering, composition: veejay
- Projection mapping: mapmap / lpmt


### Development

The project is written in C++11 and OpenGL 3.3+. Additional software
components used inside the études project are:

- CMake
- liblo
- glm

#### License

All software components developed for the project are released under
terms of the GNU General Public License 3.0. The goal is to get a
complete toolchain made of free software components. The only part
which seems to be lacking right now is the sequencing
software. Suggestions for free sequencers are very welcome!

#### Team

Patric Schmitz (<schmitz@ircam.fr>)<br>
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
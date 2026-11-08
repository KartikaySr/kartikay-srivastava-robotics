# Kartikay Srivastava Robotics

**Developed and maintained by Kartikay Srivastava.**

Kartikay Srivastava Robotics is Kartikay Srivastava's edition of a self-contained C++ robotics library for rigid body kinematics and dynamics, motion planning, and control. It includes spatial vector algebra, multibody systems, hardware abstraction, collision detection, and visualization for Linux, macOS, and Windows.

This edition builds on the work acknowledged in [CONTRIBUTORS.md](CONTRIBUTORS.md). The `rl` namespace, headers, build options, library targets, and executable identifiers are retained for compatibility.

## Build from source

Use a C++11 compiler and CMake 3.1 or newer. Install the dependencies required by the enabled components; these include Eigen3 for mathematics, Boost for several components, LibXml2/LibXslt for XML, and Qt/Coin3D/SoQt for graphical demos. Collision backends and hardware drivers have additional optional dependencies.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
cmake --install build --prefix ./install
```

For CMake versions older than 3.13, configure with `mkdir build`, `cd build`, and `cmake ..`; build, test, and install from that directory. Installation may require choosing a writable prefix.

Disable graphical applications with `-DRL_BUILD_DEMOS=OFF -DRL_BUILD_EXTRAS=OFF`. The `RL_BUILD_*` options select library components and tests. API documentation can be built with Doxygen using `-DRL_BUILD_DOCUMENTATION=ON`.

Build this edition from the included source. External packages and release downloads referenced in the contributor resources belong to the upstream project.

## Examples and demos

Kartikay Srivastava Robotics includes a number of demo [applications](demos) and a selection of [kinematics](examples/rlmdl), [geometry](examples/rlsg), and [path planning](examples/rlplan) examples that demonstrate how to use it for more advanced applications.

Among several others, these demo applications include

*   a tool for [converting](demos/rlRotationConverterDemo) between rotation matrices, angle axis, quaternions, and Euler angles,
*   the visualization of [collision detection](demos/rlCollisionDemo) queries that can highlight intersections, minimum distance, and penetration depth,
*   a [kinematics simulator](demos/rlCoachMdl) that uses a TCP port for joint position updates,
*   a [dynamics simulator](demos/rlSimulator) that listens for joint torque updates,
*   the calculation of a collision-free path using a [Probabilistic Roadmap](demos/rlPrmDemo) or a [Rapidly-Exploring Random Tree](demos/rlRrtDemo),
*   the visualization of [path planning](demos/rlPlanDemo) queries based on scenario definitions from an XML file,
*   robot [forward and inverse dynamics](demos/rlDynamics1Demo) using the Recursive Newton-Euler and Articulated-Body Algorithm methods,
*   the calculation of [dynamics properties](demos/rlDynamics2Demo) such as mass matrix, centrifugal and Coriolis forces, or gravity compensation,
*   the calculation and sending of a [trajectory](demos/rlAxisControllerDemo) to a robot controller based on a cubic or quintic polynomial.

## Contributors

See [CONTRIBUTORS.md](CONTRIBUTORS.md) for original contributor credits, publications, and reference resources.

## License

The included code retains its [BSD 2-Clause license](LICENSE.md), existing copyright notices, and third-party notices. Those notices acknowledge the original work; current project branding and maintenance are by Kartikay Srivastava.

# Kartikay Srivastava Robotics

**Developed and maintained by Kartikay Srivastava.**

Kartikay Srivastava Robotics is Kartikay Srivastava's edition of a self-contained C++ robotics library for rigid body kinematics and dynamics, motion planning, and control. It includes spatial vector algebra, multibody systems, hardware abstraction, collision detection, and visualization for Linux, macOS, and Windows.

This edition builds on the work acknowledged in [CONTRIBUTORS.md](CONTRIBUTORS.md). The `rl` namespace, headers, build options, library targets, and executable identifiers are retained for compatibility.

## Build from source

Use a C++17 compiler and CMake 3.1 or newer. Install the dependencies required by the enabled components; these include Eigen3 for mathematics, Boost for several components, LibXml2/LibXslt for XML, and Qt/Coin3D/SoQt for graphical demos. Collision backends and hardware drivers have additional optional dependencies.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
cmake --install build --prefix ./install
```

For CMake versions older than 3.13, configure with `mkdir build`, `cd build`, and `cmake ..`; build, test, and install from that directory. Installation may require choosing a writable prefix.

Disable graphical applications with `-DRL_BUILD_DEMOS=OFF -DRL_BUILD_EXTRAS=OFF`. The `RL_BUILD_*` options select library components and tests. API documentation can be built with Doxygen using `-DRL_BUILD_DOCUMENTATION=ON`.

Build this edition from the included source. External packages and release downloads referenced in the contributor resources belong to the upstream project.

## Desktop applications and packages

On macOS, install the desktop dependencies with Homebrew before configuring:

```sh
brew install cmake boost eigen coin3d qtbase fcl libxml2 libxslt
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(brew --prefix);$(brew --prefix qtbase);$(brew --prefix libxml2);$(brew --prefix libxslt)"
```

Launch the rotation converter directly, or open the included Puma robot in the kinematics and dynamics applications:

```sh
./build/bin/rlRotationConverterDemo
./build/bin/rlCoachMdl examples/rlsg/unimation-puma560_boxes.xml examples/rlmdl/unimation-puma560.xml
./build/bin/rlSimulator examples/rlsg/unimation-puma560_boxes.xml examples/rlmdl/unimation-puma560.xml
```

The Qt applications embed the project icon and identify Kartikay Srivastava as the project maintainer. SoQt must match the selected Qt major version for the 3D applications. Optional hardware and collision backends are enabled when their dependencies are available.

For release builds, configure with `-DRL_REQUIRE_DESKTOP=ON` to fail early if any desktop application or its dependencies are unavailable. After a successful build and test run, create a distribution archive:

```sh
cd build
cpack -G TGZ
```

Extract the archive and run programs from its `bin` directory. Models are installed under `share/rl-0.7.0/examples`. Archives include the project libraries, examples, and license/credit files. Install matching third-party runtime dependencies on the destination system. The `main` branch CI builds, tests, and uploads platform-specific archives to GitHub Actions.

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

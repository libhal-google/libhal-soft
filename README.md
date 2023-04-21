# libhal-soft
[![✅CI](https://github.com/libhal/libhal-soft/actions/workflows/ci.yml/badge.svg)](https://github.com/libhal/libhal-soft/actions/workflows/ci.yml)
[![coverage](https://libhal.github.io/libhal-soft/coverage/coverage.svg)](https://libhal.github.io/libhal-soft/coverage/)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b084e6d5962d49a9afcb275d62cd6586)](https://www.codacy.com/gh/libhal/libhal-soft/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=libhal/libhal-soft&amp;utm_campaign=Badge_Grade)
[![GitHub stars](https://img.shields.io/github/stars/libhal/libhal-soft.svg)](https://github.com/libhal/libhal-soft/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/libhal/libhal-soft.svg)](https://github.com/libhal/libhal-soft/network)
[![GitHub issues](https://img.shields.io/github/issues/libhal/libhal-soft.svg)](https://github.com/libhal/libhal-soft/issues)
[![Latest Version](https://libhal.github.io/libhal-soft/latest_version.svg)](https://github.com/libhal/libhal-soft/blob/main/conanfile.py)
[![ConanCenter Version](https://repology.org/badge/version-for-repo/conancenter/libhal-soft.svg)](https://conan.io/center/libhal-soft)

Library for generic soft drivers officially supported by libhal

Soft drivers are drivers that do not have any specific underlying hardware associated with them. They are used to emulate, give context to, or alter the behavior of interfaces. For a driver to be a soft driver it must implement or have a way to generate, construct or create implementations of hardware interfaces.

Emulation Example

---

- Emulate spi by using 2 output pins and 1 input pin.
- Emulate uart transmission with a 16-bit spi driver and some clever bit positioning.

Context Example

---

- Implement a rotary encoder by using an adc, a potentiometer and some specification of the potentiometer like min and max angle, along with min and max voltage.
- Implement a dac using multiple output pins and a set of resistors and an op amp.

Alteration example

---

- Implement an input pin that inverts the readings of an actual input pin
- Implement an i2c driver that is thread safe by taking an i2c and locking mechanism provided by the user.

In general, software drivers tend to incur some overhead so nesting them deeply will effect performance.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.

## Disclaimer

This project is not an official Google project. It is not supported by
Google and Google specifically disclaims all warranties as to its quality,
merchantability, or fitness for a particular purpose.


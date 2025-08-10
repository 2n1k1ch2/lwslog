# lwslog

**lwslog** is a lightweight, modern C++20 logging library designed to be simple, extensible, and fast.  
Version 1.0 focuses on a clean header-only core and a flexible sink system for output customization.

---

## Features (v1.0)
- **Header-only core** — easy integration into any project.
- **Log levels** — TRACE, DEBUG, INFO, WARN, ERROR, FATAL.
- **Custom sinks** — output logs to files, console, or any user-defined destination by implementing `ILogSink`.
- **Stream-style syntax** — similar to `std::ostream`
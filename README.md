<div align="center">

  <div>
    <img src="https://img.shields.io/badge/GCC-%235C2D91.svg?style=for-the-badge&logo=gcc&logoColor=white" alt="GCC" />
    <img src="https://img.shields.io/badge/Makefile-%2348A0DC.svg?style=for-the-badge&logo=gnu&logoColor=white" alt="Makefile" />
    <img src="https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  </div>

  <h3 align="center">Post API</h3>
</div>

## 📋 <a name="table">Table of Contents</a>
1. 🏃 [How to Run](#how-to-run)
2. 🔨 [How it Works](#how-it-works)
3. 🛠 [Dependencies](#dependencies)
4. 🧹 [Cleaning Up](#cleaning-up)
5. 🤝 [Contributing](#contributing)
6. 📝 [License](#license)

## 🏃 <a name="how-to-run">How to Run</a>

To run the Post API on a Windows environment, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/post-api.git
    cd post-api
    ```

2. **Ensure you have GCC installed**. You can install it via MinGW or another toolchain.

3. **Build the project**:
    ```bash
    make
    ```

4. **Run the executable**:
    ```bash
    build\socket
    ```

This will start the API, which listens for requests to create, fetch, delete, and update posts.

## 🔨 <a name="how-it-works">How it Works</a>

The Post API is a simple HTTP server built using C and the WinSock2 library. It allows clients to interact with a basic data store via HTTP requests. The API supports the following operations:

- **Create a post**: Add a new post to the data store.
- **Fetch a post**: Retrieve the content of a specific post.
- **Update a post**: Modify the content of an existing post.
- **Delete a post**: Remove a post from the data store.

## 🛠 <a name="dependencies">Dependencies</a>

- **GCC**: Used to compile the C source code.
- **Make**: Automates the build process.
- **WinSock2 Library**: Provides network communication functions. Linked using `-lws2_32`.
- **Rpcrt4 Library**: Provides UUID generation support, linked using `-lRpcrt4`.

## 🧹 <a name="cleaning-up">Cleaning Up</a>

To remove the compiled objects and executables, run:

```bash
make clean
```

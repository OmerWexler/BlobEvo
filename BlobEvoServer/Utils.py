def from_cpp_to_python(msg: str):
    return ''.join(chr(ord(letter) + 1) for letter in msg)

def from_pyhton_to_cpp(msg: str):
    return ''.join(chr(ord(letter) - 1) for letter in msg)
var abyss1 = {"entry_one" : [
  {"Prompt": "PROMPT", "Category":"w3-xlarge"},
  {"Prompt": "Abyss was a set of three challenges focused on the 3 main parts of kvm: user interaction from an elf binary, interaction with the kernel, and the hipervisor. This article focuses on the user phase.", "Category": ""},
  {"Prompt": "", "Category": ""},
  {"Prompt": "INITIAL ANALYSIS", "Category":"w3-xlarge"},
  {"Prompt": "Only two binaries concern us for this phase, user.elf and kernel.bin. User.elf was a 64 bit elf binary that emulated a virtual stack within it through the following functions:", "Category": ""},
  {"Prompt": "", "Category": ""},
  {"Prompt": "PROBLEMS IN THE KERNEL", "Category":"w3-xlarge"},
  {"Prompt": "While the binary has a non executable stack, it is using a custom kernel that does not support nx. Therefore, all parts of the binary have read, write, and executable permissions. Further analysis of the kernel in binary ninja reveals that it has an open function that will only open a few filenames, including flag.txt.", "Category": ""}
]};
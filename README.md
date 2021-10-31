Submission for a text compression challenge

Constraints:
- Text is made of english
- Text has only letters a-z and space
- No hardcoding dictionaries

Strategy implemented here:
- Build big dictionary of words used in text, huffman code those
- Huffman code characters using conditional probabilities developed [here][1] when saving dictionary

How effective this strategy is depends largely on the input size and vocabulary of the target text.

Final results:

```
┌─────────────────┬───────────────────┬───────────────────┐
│                 │ SCORE:            │ COMPRESSION RATE: │
├─────────────────┼───────────────────┼───────────────────┤
│ 7z PPMd         │ 118607            │ 22.6225           │
├─────────────────┼───────────────────┼───────────────────┤
│ bz2             │ 126054            │ 24.0429           │
├─────────────────┼───────────────────┼───────────────────┤
│ This code       │ 130139            │ 24.8221           │
├─────────────────┼───────────────────┼───────────────────┤
│ 7z LZMA2        │ 143047            │ 27.2842           │
├─────────────────┼───────────────────┼───────────────────┤
│ gz              │ 163193            │ 31.1267           │
└─────────────────┴───────────────────┴───────────────────┘
```

[1]: https://github.com/jeremy-rifkin/Markov-Huffman-Coding

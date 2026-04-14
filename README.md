# Welcome to the docs for the CFR analyzer tool

## Lettering guidelines
According to CFR title 1, chapter 1, subchapter E, part 21, subpart A (21.11) section h the organization of paragraphs are designated as follows
level 1 (a), (b), (c), etc.

level 2 (1), (2), (3), etc.

level 3 (i), (ii), (iii), etc.

level 4 (A), (B), (C), etc.

level 5 (1), (2), (3), etc.

level 6 (i), (ii), (iii), etc.

[source](https://www.ecfr.gov/current/title-1/chapter-I/subchapter-E/part-21/subpart-A/subject-group-ECFRe8a0e8af6bd5c46/section-21.11)

My XML parsing algorithm is dependent on this system as when pulling from the CFR API everything is dumped under one main child element and since some agencies may not strictly adhere to the guidelines that means that sometimes the formatting may not work as expected.
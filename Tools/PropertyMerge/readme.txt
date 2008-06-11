Tool pair implemented for dealing with large models.
When a .xme file is too large for a successful 
import, regnodes and attributes (properties)
can be stripped out from the .xme file, and 
have the import succeed with a smaller memory 
footprint.


Step1:
In order to extract the properties for each 
fco PropMiner must be used, which will
generate guid based files, each file 
containing the proper GME clibpoard 
compatible xml snippet.


Step2:
Do the special import process into GME, 
optionA: the GMEParser can ignore simply the attr and regn xml nodes.
optionB: use xslt to kill the attr and regn content from the input xme file.

Step3:
In Step2 you have created the binary file succesfully,
which contains the default attribute values, and has
no regnodes. To restore your model to the original state,
invoke PropMerger to paste back each individual model-snippet
to the original owner.


In order to have this whole approach working, GUID 
uniqueness and persistence is a strict requirement.
This is a given in GME, however GUIDs can be changed 
upon the import process, if the import is initiated 
into a NOT empty project: so in Step 2, the import must
be done into an empty project (that's the case when
GUIDs are NOT altered).
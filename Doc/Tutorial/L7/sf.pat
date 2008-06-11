$!DEFINE("_FILENAMEBASE", "$!IFDEFAULT("FileNameBase","$(Name)")")
$!TO_FILE("$!IFDEFAULT("OutputPath","")$(_FILENAMEBASE).html")
<html>
<head>
	<title>GME SFDemo - Generated by PatPlugin</title>
</head>
<body>

	<h1>PrimitiveParts</h1>

	<table align="center" width="600" cellspacing="0" cellpadding="0" border="1">
	<tr><td>Item No.</td><td>Name</td><td>Firing</td><td>Script</td><td>Priority</td></tr>
	$!DEFINE("INDEX","1")
	$!EVAL_FORALL("R:PrimitiveParts","<tr>\n<td>$!POSTINCR("INDEX")</td>\
		<td>$Name</td><td>$Firing</td><td>$Script</td><td>$Priority</td>\n</tr>\n")
	</table>

	<br><br>

	<h1>CompoundParts</h1>

	$!DEFINE("INDEX","1")
	$!EVAL_FORALL("R:CompoundParts",\
		"<table align=\"center\" width=\"600\" cellspacing=\"0\" cellpadding=\"0\" border=\"1\">\n\
		<tr>\n<th colspan=\"5\" align=\"left\"><b>$Name</b></th>\n</tr>\n\
		<tr>\n<td>Item No.</td><td>Name</td><td>Firing</td><td>Script</td><td>Priority</td>\n</tr>\n\
		$!EVAL_FORALL("R:PrimitiveParts","<tr>\n<td>$!POSTINCR("INDEX")</td>\
			<td>$Name</td><td>$Firing</td><td>$Script</td><td>$Priority</td>\n</tr>\n")\</table>")

	<br><br>

	<h1>PrimitiveParts->PrimitiveParts dataflow connections</h1>

	<table align="center" width="600" cellspacing="0" cellpadding="0" border="1">
	<tr><td>Source</td><td>OutputPort</td><td>Destination</td></tr>
	$!EVAL_FORALL("R:PrimitiveParts","$!DEFINE("Part",$Name)$!EVAL_FORALL("R:OutputSignals","$!DEFINE("Port",$Name)$!EVAL_FORALL("Dst:DataflowConn","$!EVAL_WITH("Parent","<tr><td>$Part</td><td>$Port</td><td>$Name</td></tr>\n")")")")
	</table>
	
</body>
</html>
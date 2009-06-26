<?xml version='1.0'?> 
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:fo="http://www.w3.org/1999/XSL/Format"
    version="1.0"> 

<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/fo/docbook.xsl"/> 

<xsl:param name="fop1.extensions">1</xsl:param>

<!-- render gui* elements in bold -->
<xsl:template match="guibutton">
  <xsl:call-template name="inline.boldseq"/>
</xsl:template>
<xsl:template match="guilabel">
  <xsl:call-template name="inline.boldseq"/>
</xsl:template>
<xsl:template match="guimenu">
  <xsl:call-template name="inline.boldseq"/>
</xsl:template>
<xsl:template match="guimenuitem">
  <xsl:call-template name="inline.boldseq"/>
</xsl:template>
<xsl:template match="guisubmenu">
  <xsl:call-template name="inline.boldseq"/>
</xsl:template>


</xsl:stylesheet>  

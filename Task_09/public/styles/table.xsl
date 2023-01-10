<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <body>
                <xsl:for-each select="addresses/address">
                    <div class="card" style="border: 1px solid red; margin: 1rem; padding: 1rem;">
                        <div class="card-header">
                            <h3>
                                <xsl:value-of select="name"/>
                                <xsl:value-of select="surname"/>
                            </h3>
                        </div>
                        <div class="card-body">
                            <p>
                                <b>Street:</b>
                                <xsl:value-of select="street"/>
                                <xsl:value-of select="houseNumber"/>
                            </p>
                            <p>
                                <b>PLZ:</b>
                                <xsl:value-of select="PLZ"/>
                                <b>City:</b>
                                <xsl:value-of select="city"/>
                            </p>
                            <p>
                                <b>Telephone Number:</b>
                                <xsl:value-of select="telephoneNumber"/>
                            </p>
                            <p>
                                <b>Email:</b>
                                <xsl:value-of select="email"/>
                            </p>
                        </div>
                    </div>
                </xsl:for-each>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>

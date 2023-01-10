<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <body>
                <h2>Address List</h2>
                <table border="1">
                    <tr>
                        <th>Full Name</th>
                        <th>Telephone Number</th>
                    </tr>
                    <xsl:for-each select="addresses/address">
                        <tr>
                            <td>
                                <span>
                                    <xsl:value-of select="name"/>
                                </span>
                                <span>
                                    <xsl:value-of select="surname"/>
                                </span>
                            </td>
                            <td>
                                <xsl:value-of select="telephoneNumber"/>
                            </td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>

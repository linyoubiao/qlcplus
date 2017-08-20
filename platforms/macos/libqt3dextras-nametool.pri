LIBQT3DEXTRAS_DIR      = Qt3DExtras.framework/Versions/5
LIBQT3DEXTRAS_FILE     = Qt3DExtras
LIBQT3DEXTRAS_FILEPATH = $$LIBQT3DEXTRAS_DIR/$$LIBQT3DEXTRAS_FILE

LIBQT3DEXTRAS_INSTALL_NAME_TOOL = install_name_tool -change $$(QTDIR)/lib/$$LIBQT3DEXTRAS_FILEPATH \
            @executable_path/../$$LIBSDIR/$$LIBQT3DEXTRAS_DIR/$$LIBQT3DEXTRAS_FILE

contains(QT, 3dextras) {
    !isEmpty(nametool.commands) {
        nametool.commands += "&&"
    }

    nametool.commands += $$LIBQT3DEXTRAS_INSTALL_NAME_TOOL $$OUTFILE
}

LIBQT3DEXTRAS.path   = $$INSTALLROOT/$$LIBSDIR/$$LIBQT3DEXTRAS_DIR
LIBQT3DEXTRAS.files += $$(QTDIR)/lib/$$LIBQT3DEXTRAS_FILEPATH

LIBQT3DEXTRAS_INSTALL_NAME_TOOL_ID = install_name_tool -id @executable_path/../$$LIBSDIR/$$LIBQT3DEXTRAS_DIR/$$LIBQT3DEXTRAS_FILE \
                        $$INSTALLROOT/$$LIBSDIR/$$LIBQT3DEXTRAS_DIR/$$LIBQT3DEXTRAS_FILE
LIBQT3DEXTRAS_ID.path     = $$INSTALLROOT/$$LIBSDIR/$$LIBQT3DEXTRAS_DIR
LIBQT3DEXTRAS_ID.commands = $$LIBQT3DEXTRAS_INSTALL_NAME_TOOL_ID
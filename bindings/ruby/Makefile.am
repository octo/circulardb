EXTRA_DIST = setup.rb lib ext

all-local:
	$(RUBY) setup.rb config
	$(RUBY) setup.rb setup

# Don't add $(prefix) here, since Ruby's config.rb has it hardcoded in sitedir.
install-exec-hook:
	$(RUBY) setup.rb install --prefix=$(DESTDIR)

# Make sure this doesn't fail if Ruby is not configured.
clean-local:
	RUBY=$(RUBY) ; if test -z "$$RUBY" ; then RUBY=: ; fi ; \
	$$RUBY setup.rb clean

check-local: all

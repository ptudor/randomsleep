# Keep Version in sync with VERSION in GNUmakefile.
Name:           randomsleep
Version:        1.0.1
Release:        1%{?dist}
Summary:        Cryptographically secure random delay utility for cron jitter

License:        ISC
URL:            https://github.com/ptudor/%{name}
Source0:        %{url}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  make

%description
randomsleep introduces a cryptographically secure random delay, intended for
cron jobs to add jitter and avoid "thundering herd" problems where many hosts
contact a central service or start heavy jobs at the same instant.

On Linux it draws randomness from the getrandom(2) syscall and uses rejection
sampling to produce an unbiased delay between a floor and a ceiling (default
0 to 1800 seconds).

%prep
%autosetup

%build
%set_build_flags
%make_build

%install
%make_install PREFIX=%{_prefix}

%files
%license LICENSE
%doc README.md
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1*

%changelog
* Fri Jun 26 2026 Patrick Tudor <ptudor@ptudor.net> - 1.0.1-1
- Initial RPM packaging (first packaged release; 1.0.0 was source only).

#! /usr/bin/env atf-sh

TESTS_DIR=$(atf_get_srcdir)/P2Tests

tests=""

for path in ${TESTS_DIR}/*.ss
do
    file=${path##${TESTS_DIR}/}
    name=${file%%.ss}

    atf_test_case ${name}

    eval "${name}_head() {
        atf_set descr ${file}
        atf_set require.files ${path}
        atf_set require.progs $(atf_get_srcdir)/P2.out
    }

    ${name}_body() {
        atf_check -o match:'^0 errors' \
                  $(atf_get_srcdir)/P2.out ${path}
    }"

    tests="${tests} ${name}"
done

for path in ${TESTS_DIR}/*.ss.bad
do
    file=${path##${TESTS_DIR}/}
    name=${file%%.ss.bad}_bad

    atf_test_case ${name}

    eval "${name}_head() {
        atf_set descr ${file}
        atf_set require.files ${path}
        atf_set require.progs $(atf_get_srcdir)/P2.out
    }

    ${name}_body() {
        atf_check -o not-match:'^0 errors' \
                  -s exit:1 \
                  $(atf_get_srcdir)/P2.out ${path}
    }"

    tests="${tests} ${name}"
done

atf_init_test_cases() {
    for t in ${tests}
    do
        atf_add_test_case ${t}
    done
}

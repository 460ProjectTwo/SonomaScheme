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

#-----------------------------------------

atf_test_case H3oc1

H3oc1_head() {
    atf_set descr H3oc1.ss
    atf_set require.files $(atf_get_srcdir)/tests/H3oc1.ss
    atf_set require.progs $(atf_get_srcdir)/P2.out
}

H3oc1_body() {
    cp $(atf_get_srcdir)/tests/H3oc1.ss test.ss
    atf_check -o ignore -e ignore $(atf_get_srcdir)/P2.out test.ss
    atf_check diff -wu $(atf_get_srcdir)/tests/H3oc1.p2 test.p2
}

H3oc1_cleanup() {
    rm test.p1 test.p2 test.lst test.dbg test.ss
}

#-----------------------------------------

atf_test_case H3oc2

H3oc2_head() {
    atf_set descr H3oc2.ss
    atf_set require.files $(atf_get_srcdir)/tests/H3oc2.ss
    atf_set require.progs $(atf_get_srcdir)/P2.out
}

H3oc2_body() {
    cp $(atf_get_srcdir)/tests/H3oc2.ss test.ss
    atf_check -o ignore -e ignore $(atf_get_srcdir)/P2.out test.ss
    atf_check diff -wu $(atf_get_srcdir)/tests/H3oc2.p2 test.p2
}

H3oc2_cleanup() {
    rm test.p1 test.p2 test.lst test.dbg test.ss
}

#-----------------------------------------

atf_init_test_cases() {
    for t in ${tests}
    do
        atf_add_test_case ${t}
    done
    atf_add_test_case H3oc1
    atf_add_test_case H3oc2
}

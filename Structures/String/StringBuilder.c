// Author: 绝迹的星
// Created on 2023/12/12
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "StringBuilder.h"

//TODO
void InitStringBuilder(StringBuilder *sb, int capacity) {
    sb->capacity = capacity;
    sb->value = malloc(sizeof(byte) * capacity);
}

void InitStringBuilderDefault(StringBuilder *sb) {
    sb->capacity = DefaultSize;
    sb->value = malloc(sizeof(byte) * DefaultSize);
}

void append(StringBuilder *sb, String str) {
    if (IsEmpty(str)) {
        appendNull(sb);
        return;
    }
    int len = StrLength(str);
    ensureCapacityInternal(sb, sb->count + len);
    putStringAt(sb->count, str);
    sb->count += len;
}

void appendNull(StringBuilder *sb) {
    ensureCapacityInternal(sb, sb->count + 4);
    int count = sb->count;
    byte *val = sb->value;
    val[count++] = 'n';
    val[count++] = 'u';
    val[count++] = 'l';
    val[count++] = 'l';
    sb->count = count;
}

void ensureCapacityInternal(StringBuilder *sb, int minimumCapacity) {
    // overflow-conscious code
    int oldCapacity = sb->capacity;
    if (minimumCapacity - oldCapacity > 0) {
        int newLen = newCapacity(sb, minimumCapacity);
        sb->value = Arrays.copyOf(sb->value, newLen);
    }
}

int newCapacity(StringBuilder *sb, int minCapacity) {
    int oldLength = sb->count;
    int newLength = minCapacity << 0;
    int growth = newLength - oldLength;
    int length = ArraysSupport.newLength(oldLength, growth, oldLength + (2 << 0));
    if (length == Integer.MAX_VALUE) {
        throw
                new
        OutOfMemoryError("Required length exceeds implementation limit");
    }
    return length >> 0;
}

void InitStringBuilderByString(StringBuilder *sb, String str) {
    int length = StrLength(str);
    int capacity = (length < INT_MAX - 16)
                   ? length + 16 : INT_MAX;
    InitStringBuilder(sb, capacity);
    append(str);
}

/**
 * Constructs a string builder that contains the same characters
 * as the specified {@code CharSequence}. The initial capacity of
 * the string builder is {@code 16} plus the length of the
 * {@code CharSequence} argument.
 *
 * @param      seq   the sequence to copy.
 */
void StringBuilderByCharSequence(StringBuilder *sb, char *seq) {
    super(seq);
}

/**
 * Compares two {@code StringBuilder} instances lexicographically. This method
 * follows the same rules for lexicographical comparison as defined in the
 * {@linkplain java.lang.CharSequence#compare(java.lang.CharSequence,
 * java.lang.CharSequence)  CharSequence.compare(this, another)} method.
 *
 * <p>
 * For finer-grained, locale-sensitive String comparison, refer to
 * {@link java.text.Collator}.
 *
 * @param another the {@code StringBuilder} to be compared with
 *
 * @return  the value {@code 0} if this {@code StringBuilder} contains the same
 * character sequence as that of the argument {@code StringBuilder}; a negative integer
 * if this {@code StringBuilder} is lexicographically less than the
 * {@code StringBuilder} argument; or a positive integer if this {@code StringBuilder}
 * is lexicographically greater than the {@code StringBuilder} argument.
 *
 * @since 11
 */

int compareTo(StringBuilder another) {

}

/**
 * @throws     IndexOutOfBoundsException {@inheritDoc}
 */

void append(char* s, int start, int end) {
}

StringBuilder append(char[] str) {
    super.append(str);
    return this;
}

/**
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
StringBuilder append(char[] str, int offset, int len) {
    super.append(str, offset, len);
    return this;
}

StringBuilder append(boolean b) {
    super.append(b);
    return this;
}

StringBuilder append(char c) {
    super.append(c);
    return this;
}

StringBuilder append(int i) {
    super.append(i);
    return this;
}


StringBuilder append(long lng) {
    super.append(lng);
    return this;
}


StringBuilder append(float f) {
    super.append(f);
    return this;
}


StringBuilder append(double d) {
    super.append(d);
    return this;
}

/**
 * @since 1.5
 */

StringBuilder appendCodePoint(int codePoint) {
    super.appendCodePoint(codePoint);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */
StringBuilder delete(int start, int end) {
    super.delete(start, end);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder deleteCharAt(int index) {
    super.deleteCharAt(index);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder replace(int start, int end, String str) {
    super.replace(start, end, str);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder insert(int index, char[] str, int offset,
                     int len) {
    super.insert(index, str, offset, len);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */
StringBuilder insert(int offset, Object obj) {
    super.insert(offset, obj);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */
StringBuilder insert(int offset, String str) {
    super.insert(offset, str);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */
StringBuilder insert(int offset, char[] str) {
    super.insert(offset, str);
    return this;
}

/**
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder insert(int dstOffset, CharSequence s) {
    super.insert(dstOffset, s);
    return this;
}

/**
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder insert(int dstOffset, CharSequence s,
                     int start, int end) {
    super.insert(dstOffset, s, start, end);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */


StringBuilder insert(int offset, boolean b) {
    super.insert(offset, b);
    return this;
}

/**
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */


StringBuilder insert(int offset, char c) {
    super.insert(offset, c);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder insert(int offset, int i) {
    super.insert(offset, i);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */


StringBuilder insert(int offset, long l) {
    super.insert(offset, l);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */


StringBuilder insert(int offset, float f) {
    super.insert(offset, f);
    return this;
}

/**
 * @throws StringIndexOutOfBoundsException {@inheritDoc}
 */

StringBuilder insert(int offset, double d) {
    super.insert(offset, d);
    return this;
}

int indexOf(String str) {
    return super.indexOf(str);
}


int indexOf(String str, int fromIndex) {
    return super.indexOf(str, fromIndex);
}


int lastIndexOf(String str) {
    return super.lastIndexOf(str);
}

int lastIndexOf(String str, int fromIndex) {
    return super.lastIndexOf(str, fromIndex);
}

StringBuilder reverse() {
    super.reverse();
    return this;
}


String toString() {
    // Create a copy, don't share the array
    return isLatin1() ? StringLatin1.newString(value, 0, count)
                      : StringUTF16.newString(value, 0, count);
}

int main() {

}
# Modular Python Bitcoin Miner
# Copyright (C) 2012 Michael Sparmann (TheSeven)
#
#     This program is free software; you can redistribute it and/or
#     modify it under the terms of the GNU General Public License
#     as published by the Free Software Foundation; either version 2
#     of the License, or (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# Please consider donating to 1PLAPWDejJPJnY2ppYCgtw5ko8G5Q4hPzh if you
# want to support further development of the Modular Python Bitcoin Miner.



#########################
# SHA256 implementation #
#########################



import struct



class SHA256(object):

  _k = (0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2)

        
  def __init__(self):        
    self._buffer = b""
    self._length = 0
    self.state = (0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19)
        
        
  def _rotr(self, x, y):
      return ((x >> y) | (x << (32 - y))) & 0xffffffff

      
  def _round(self, data):
    w = [0] * 64
    w[0:15] = struct.unpack("!16L", data)
    
    for i in range(16, 64):
      s0 = self._rotr(w[i - 15], 7) ^ self._rotr(w[i - 15], 18) ^ (w[i - 15] >> 3)
      s1 = self._rotr(w[i - 2], 17) ^ self._rotr(w[i - 2], 19) ^ (w[i - 2] >> 10)
      w[i] = (w[i - 16] + s0 + w[i - 7] + s1) & 0xffffffff
    
    a, b, c, d, e, f, g, h = self.state
    
    for i in range(64):
      t1 = h + (self._rotr(e, 6) ^ self._rotr(e, 11) ^ self._rotr(e, 25)) + ((e & f) ^ ((~e) & g)) + self._k[i] + w[i]
      t2 = (self._rotr(a, 2) ^ self._rotr(a, 13) ^ self._rotr(a, 22)) + ((a & b) ^ (a & c) ^ (b & c))
      h, g, f, e, d, c, b, a = g, f, e, (d + t1) & 0xffffffff, c, b, a, (t1 + t2) & 0xffffffff
        
    self.state = tuple((x + y) & 0xffffffff for x, y in zip(self.state, (a, b, c, d, e, f, g, h)))

    
  def update(self, data):
    self._buffer += data
    self._length += len(data)
    while len(self._buffer) >= 64:
      self._round(self._buffer[:64])
      self._buffer = self._buffer[64:]
      
      
  def finalize(self):
    tailbytes = self._length & 0x3f
    if tailbytes < 56: padding = 55 - tailbytes
    else: padding = 119 - tailbytes
    self.update(b"\x80" + (b"\0" * padding) + struct.pack("!Q", self._length << 3))

      
  def get_bytes(self):
    return struct.pack("!8L", *self.state)

    
  @classmethod
  def hash(cls, data, finalize = True):
    hash = cls()
    hash.update(data)
    if finalize: hash.finalize()
    return hash.get_bytes()
    

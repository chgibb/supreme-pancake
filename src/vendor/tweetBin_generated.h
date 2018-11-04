// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_TWEETBIN_H_
#define FLATBUFFERS_GENERATED_TWEETBIN_H_

#include "flatbuffers/flatbuffers.h"

struct Tweet;
struct TweetT;

struct TweetBin;
struct TweetBinT;

struct TweetT : public flatbuffers::NativeTable {
  typedef Tweet TableType;
  std::string text;
  std::string textHash;
  std::string user;
  std::string date;
  std::string id;
  std::string committed;
  TweetT() {
  }
};

struct Tweet FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TweetT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TEXT = 4,
    VT_TEXTHASH = 6,
    VT_USER = 8,
    VT_DATE = 10,
    VT_ID = 12,
    VT_COMMITTED = 14
  };
  const flatbuffers::String *text() const {
    return GetPointer<const flatbuffers::String *>(VT_TEXT);
  }
  const flatbuffers::String *textHash() const {
    return GetPointer<const flatbuffers::String *>(VT_TEXTHASH);
  }
  const flatbuffers::String *user() const {
    return GetPointer<const flatbuffers::String *>(VT_USER);
  }
  const flatbuffers::String *date() const {
    return GetPointer<const flatbuffers::String *>(VT_DATE);
  }
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  const flatbuffers::String *committed() const {
    return GetPointer<const flatbuffers::String *>(VT_COMMITTED);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TEXT) &&
           verifier.VerifyString(text()) &&
           VerifyOffset(verifier, VT_TEXTHASH) &&
           verifier.VerifyString(textHash()) &&
           VerifyOffset(verifier, VT_USER) &&
           verifier.VerifyString(user()) &&
           VerifyOffset(verifier, VT_DATE) &&
           verifier.VerifyString(date()) &&
           VerifyOffset(verifier, VT_ID) &&
           verifier.VerifyString(id()) &&
           VerifyOffset(verifier, VT_COMMITTED) &&
           verifier.VerifyString(committed()) &&
           verifier.EndTable();
  }
  TweetT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(TweetT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<Tweet> Pack(flatbuffers::FlatBufferBuilder &_fbb, const TweetT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct TweetBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_text(flatbuffers::Offset<flatbuffers::String> text) {
    fbb_.AddOffset(Tweet::VT_TEXT, text);
  }
  void add_textHash(flatbuffers::Offset<flatbuffers::String> textHash) {
    fbb_.AddOffset(Tweet::VT_TEXTHASH, textHash);
  }
  void add_user(flatbuffers::Offset<flatbuffers::String> user) {
    fbb_.AddOffset(Tweet::VT_USER, user);
  }
  void add_date(flatbuffers::Offset<flatbuffers::String> date) {
    fbb_.AddOffset(Tweet::VT_DATE, date);
  }
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(Tweet::VT_ID, id);
  }
  void add_committed(flatbuffers::Offset<flatbuffers::String> committed) {
    fbb_.AddOffset(Tweet::VT_COMMITTED, committed);
  }
  explicit TweetBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TweetBuilder &operator=(const TweetBuilder &);
  flatbuffers::Offset<Tweet> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Tweet>(end);
    return o;
  }
};

inline flatbuffers::Offset<Tweet> CreateTweet(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> text = 0,
    flatbuffers::Offset<flatbuffers::String> textHash = 0,
    flatbuffers::Offset<flatbuffers::String> user = 0,
    flatbuffers::Offset<flatbuffers::String> date = 0,
    flatbuffers::Offset<flatbuffers::String> id = 0,
    flatbuffers::Offset<flatbuffers::String> committed = 0) {
  TweetBuilder builder_(_fbb);
  builder_.add_committed(committed);
  builder_.add_id(id);
  builder_.add_date(date);
  builder_.add_user(user);
  builder_.add_textHash(textHash);
  builder_.add_text(text);
  return builder_.Finish();
}

inline flatbuffers::Offset<Tweet> CreateTweetDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *text = nullptr,
    const char *textHash = nullptr,
    const char *user = nullptr,
    const char *date = nullptr,
    const char *id = nullptr,
    const char *committed = nullptr) {
  return CreateTweet(
      _fbb,
      text ? _fbb.CreateString(text) : 0,
      textHash ? _fbb.CreateString(textHash) : 0,
      user ? _fbb.CreateString(user) : 0,
      date ? _fbb.CreateString(date) : 0,
      id ? _fbb.CreateString(id) : 0,
      committed ? _fbb.CreateString(committed) : 0);
}

flatbuffers::Offset<Tweet> CreateTweet(flatbuffers::FlatBufferBuilder &_fbb, const TweetT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

struct TweetBinT : public flatbuffers::NativeTable {
  typedef TweetBin TableType;
  std::vector<std::unique_ptr<TweetT>> bucket0;
  std::vector<std::unique_ptr<TweetT>> bucket1;
  std::vector<std::unique_ptr<TweetT>> bucket2;
  std::vector<std::unique_ptr<TweetT>> bucket3;
  std::vector<std::unique_ptr<TweetT>> bucket4;
  std::vector<std::unique_ptr<TweetT>> bucket5;
  std::vector<std::unique_ptr<TweetT>> bucket6;
  std::vector<std::unique_ptr<TweetT>> bucket7;
  std::vector<std::unique_ptr<TweetT>> bucket8;
  std::vector<std::unique_ptr<TweetT>> bucket9;
  std::vector<std::unique_ptr<TweetT>> bucketA;
  std::vector<std::unique_ptr<TweetT>> bucketB;
  std::vector<std::unique_ptr<TweetT>> bucketC;
  std::vector<std::unique_ptr<TweetT>> bucketD;
  std::vector<std::unique_ptr<TweetT>> bucketE;
  std::vector<std::unique_ptr<TweetT>> bucketF;
  TweetBinT() {
  }
};

struct TweetBin FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef TweetBinT NativeTableType;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BUCKET0 = 4,
    VT_BUCKET1 = 6,
    VT_BUCKET2 = 8,
    VT_BUCKET3 = 10,
    VT_BUCKET4 = 12,
    VT_BUCKET5 = 14,
    VT_BUCKET6 = 16,
    VT_BUCKET7 = 18,
    VT_BUCKET8 = 20,
    VT_BUCKET9 = 22,
    VT_BUCKETA = 24,
    VT_BUCKETB = 26,
    VT_BUCKETC = 28,
    VT_BUCKETD = 30,
    VT_BUCKETE = 32,
    VT_BUCKETF = 34
  };
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket0() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket1() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET1);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket2() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET2);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket3() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET3);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket4() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET4);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket5() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET5);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket6() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET6);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket7() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET7);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket8() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET8);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucket9() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKET9);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketA() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETA);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketB() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETB);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketC() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETC);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketD() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETD);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketE() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *bucketF() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<Tweet>> *>(VT_BUCKETF);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_BUCKET0) &&
           verifier.VerifyVector(bucket0()) &&
           verifier.VerifyVectorOfTables(bucket0()) &&
           VerifyOffset(verifier, VT_BUCKET1) &&
           verifier.VerifyVector(bucket1()) &&
           verifier.VerifyVectorOfTables(bucket1()) &&
           VerifyOffset(verifier, VT_BUCKET2) &&
           verifier.VerifyVector(bucket2()) &&
           verifier.VerifyVectorOfTables(bucket2()) &&
           VerifyOffset(verifier, VT_BUCKET3) &&
           verifier.VerifyVector(bucket3()) &&
           verifier.VerifyVectorOfTables(bucket3()) &&
           VerifyOffset(verifier, VT_BUCKET4) &&
           verifier.VerifyVector(bucket4()) &&
           verifier.VerifyVectorOfTables(bucket4()) &&
           VerifyOffset(verifier, VT_BUCKET5) &&
           verifier.VerifyVector(bucket5()) &&
           verifier.VerifyVectorOfTables(bucket5()) &&
           VerifyOffset(verifier, VT_BUCKET6) &&
           verifier.VerifyVector(bucket6()) &&
           verifier.VerifyVectorOfTables(bucket6()) &&
           VerifyOffset(verifier, VT_BUCKET7) &&
           verifier.VerifyVector(bucket7()) &&
           verifier.VerifyVectorOfTables(bucket7()) &&
           VerifyOffset(verifier, VT_BUCKET8) &&
           verifier.VerifyVector(bucket8()) &&
           verifier.VerifyVectorOfTables(bucket8()) &&
           VerifyOffset(verifier, VT_BUCKET9) &&
           verifier.VerifyVector(bucket9()) &&
           verifier.VerifyVectorOfTables(bucket9()) &&
           VerifyOffset(verifier, VT_BUCKETA) &&
           verifier.VerifyVector(bucketA()) &&
           verifier.VerifyVectorOfTables(bucketA()) &&
           VerifyOffset(verifier, VT_BUCKETB) &&
           verifier.VerifyVector(bucketB()) &&
           verifier.VerifyVectorOfTables(bucketB()) &&
           VerifyOffset(verifier, VT_BUCKETC) &&
           verifier.VerifyVector(bucketC()) &&
           verifier.VerifyVectorOfTables(bucketC()) &&
           VerifyOffset(verifier, VT_BUCKETD) &&
           verifier.VerifyVector(bucketD()) &&
           verifier.VerifyVectorOfTables(bucketD()) &&
           VerifyOffset(verifier, VT_BUCKETE) &&
           verifier.VerifyVector(bucketE()) &&
           verifier.VerifyVectorOfTables(bucketE()) &&
           VerifyOffset(verifier, VT_BUCKETF) &&
           verifier.VerifyVector(bucketF()) &&
           verifier.VerifyVectorOfTables(bucketF()) &&
           verifier.EndTable();
  }
  TweetBinT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(TweetBinT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<TweetBin> Pack(flatbuffers::FlatBufferBuilder &_fbb, const TweetBinT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct TweetBinBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_bucket0(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket0) {
    fbb_.AddOffset(TweetBin::VT_BUCKET0, bucket0);
  }
  void add_bucket1(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket1) {
    fbb_.AddOffset(TweetBin::VT_BUCKET1, bucket1);
  }
  void add_bucket2(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket2) {
    fbb_.AddOffset(TweetBin::VT_BUCKET2, bucket2);
  }
  void add_bucket3(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket3) {
    fbb_.AddOffset(TweetBin::VT_BUCKET3, bucket3);
  }
  void add_bucket4(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket4) {
    fbb_.AddOffset(TweetBin::VT_BUCKET4, bucket4);
  }
  void add_bucket5(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket5) {
    fbb_.AddOffset(TweetBin::VT_BUCKET5, bucket5);
  }
  void add_bucket6(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket6) {
    fbb_.AddOffset(TweetBin::VT_BUCKET6, bucket6);
  }
  void add_bucket7(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket7) {
    fbb_.AddOffset(TweetBin::VT_BUCKET7, bucket7);
  }
  void add_bucket8(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket8) {
    fbb_.AddOffset(TweetBin::VT_BUCKET8, bucket8);
  }
  void add_bucket9(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket9) {
    fbb_.AddOffset(TweetBin::VT_BUCKET9, bucket9);
  }
  void add_bucketA(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketA) {
    fbb_.AddOffset(TweetBin::VT_BUCKETA, bucketA);
  }
  void add_bucketB(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketB) {
    fbb_.AddOffset(TweetBin::VT_BUCKETB, bucketB);
  }
  void add_bucketC(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketC) {
    fbb_.AddOffset(TweetBin::VT_BUCKETC, bucketC);
  }
  void add_bucketD(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketD) {
    fbb_.AddOffset(TweetBin::VT_BUCKETD, bucketD);
  }
  void add_bucketE(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketE) {
    fbb_.AddOffset(TweetBin::VT_BUCKETE, bucketE);
  }
  void add_bucketF(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketF) {
    fbb_.AddOffset(TweetBin::VT_BUCKETF, bucketF);
  }
  explicit TweetBinBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TweetBinBuilder &operator=(const TweetBinBuilder &);
  flatbuffers::Offset<TweetBin> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TweetBin>(end);
    return o;
  }
};

inline flatbuffers::Offset<TweetBin> CreateTweetBin(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket0 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket1 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket2 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket3 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket4 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket5 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket6 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket7 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket8 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucket9 = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketA = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketB = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketC = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketD = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketE = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Tweet>>> bucketF = 0) {
  TweetBinBuilder builder_(_fbb);
  builder_.add_bucketF(bucketF);
  builder_.add_bucketE(bucketE);
  builder_.add_bucketD(bucketD);
  builder_.add_bucketC(bucketC);
  builder_.add_bucketB(bucketB);
  builder_.add_bucketA(bucketA);
  builder_.add_bucket9(bucket9);
  builder_.add_bucket8(bucket8);
  builder_.add_bucket7(bucket7);
  builder_.add_bucket6(bucket6);
  builder_.add_bucket5(bucket5);
  builder_.add_bucket4(bucket4);
  builder_.add_bucket3(bucket3);
  builder_.add_bucket2(bucket2);
  builder_.add_bucket1(bucket1);
  builder_.add_bucket0(bucket0);
  return builder_.Finish();
}

inline flatbuffers::Offset<TweetBin> CreateTweetBinDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket0 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket1 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket2 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket3 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket4 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket5 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket6 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket7 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket8 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucket9 = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketA = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketB = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketC = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketD = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketE = nullptr,
    const std::vector<flatbuffers::Offset<Tweet>> *bucketF = nullptr) {
  return CreateTweetBin(
      _fbb,
      bucket0 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket0) : 0,
      bucket1 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket1) : 0,
      bucket2 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket2) : 0,
      bucket3 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket3) : 0,
      bucket4 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket4) : 0,
      bucket5 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket5) : 0,
      bucket6 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket6) : 0,
      bucket7 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket7) : 0,
      bucket8 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket8) : 0,
      bucket9 ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucket9) : 0,
      bucketA ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketA) : 0,
      bucketB ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketB) : 0,
      bucketC ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketC) : 0,
      bucketD ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketD) : 0,
      bucketE ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketE) : 0,
      bucketF ? _fbb.CreateVector<flatbuffers::Offset<Tweet>>(*bucketF) : 0);
}

flatbuffers::Offset<TweetBin> CreateTweetBin(flatbuffers::FlatBufferBuilder &_fbb, const TweetBinT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline TweetT *Tweet::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new TweetT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void Tweet::UnPackTo(TweetT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = text(); if (_e) _o->text = _e->str(); };
  { auto _e = textHash(); if (_e) _o->textHash = _e->str(); };
  { auto _e = user(); if (_e) _o->user = _e->str(); };
  { auto _e = date(); if (_e) _o->date = _e->str(); };
  { auto _e = id(); if (_e) _o->id = _e->str(); };
  { auto _e = committed(); if (_e) _o->committed = _e->str(); };
}

inline flatbuffers::Offset<Tweet> Tweet::Pack(flatbuffers::FlatBufferBuilder &_fbb, const TweetT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateTweet(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<Tweet> CreateTweet(flatbuffers::FlatBufferBuilder &_fbb, const TweetT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const TweetT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _text = _o->text.empty() ? 0 : _fbb.CreateString(_o->text);
  auto _textHash = _o->textHash.empty() ? 0 : _fbb.CreateString(_o->textHash);
  auto _user = _o->user.empty() ? 0 : _fbb.CreateString(_o->user);
  auto _date = _o->date.empty() ? 0 : _fbb.CreateString(_o->date);
  auto _id = _o->id.empty() ? 0 : _fbb.CreateString(_o->id);
  auto _committed = _o->committed.empty() ? 0 : _fbb.CreateString(_o->committed);
  return CreateTweet(
      _fbb,
      _text,
      _textHash,
      _user,
      _date,
      _id,
      _committed);
}

inline TweetBinT *TweetBin::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = new TweetBinT();
  UnPackTo(_o, _resolver);
  return _o;
}

inline void TweetBin::UnPackTo(TweetBinT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = bucket0(); if (_e) { _o->bucket0.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket0[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket1(); if (_e) { _o->bucket1.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket1[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket2(); if (_e) { _o->bucket2.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket2[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket3(); if (_e) { _o->bucket3.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket3[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket4(); if (_e) { _o->bucket4.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket4[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket5(); if (_e) { _o->bucket5.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket5[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket6(); if (_e) { _o->bucket6.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket6[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket7(); if (_e) { _o->bucket7.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket7[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket8(); if (_e) { _o->bucket8.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket8[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucket9(); if (_e) { _o->bucket9.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucket9[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketA(); if (_e) { _o->bucketA.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketA[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketB(); if (_e) { _o->bucketB.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketB[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketC(); if (_e) { _o->bucketC.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketC[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketD(); if (_e) { _o->bucketD.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketD[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketE(); if (_e) { _o->bucketE.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketE[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
  { auto _e = bucketF(); if (_e) { _o->bucketF.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->bucketF[_i] = std::unique_ptr<TweetT>(_e->Get(_i)->UnPack(_resolver)); } } };
}

inline flatbuffers::Offset<TweetBin> TweetBin::Pack(flatbuffers::FlatBufferBuilder &_fbb, const TweetBinT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateTweetBin(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<TweetBin> CreateTweetBin(flatbuffers::FlatBufferBuilder &_fbb, const TweetBinT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const TweetBinT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _bucket0 = _o->bucket0.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket0.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket0[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket1 = _o->bucket1.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket1.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket1[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket2 = _o->bucket2.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket2.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket2[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket3 = _o->bucket3.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket3.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket3[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket4 = _o->bucket4.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket4.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket4[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket5 = _o->bucket5.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket5.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket5[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket6 = _o->bucket6.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket6.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket6[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket7 = _o->bucket7.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket7.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket7[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket8 = _o->bucket8.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket8.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket8[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucket9 = _o->bucket9.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucket9.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucket9[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketA = _o->bucketA.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketA.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketA[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketB = _o->bucketB.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketB.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketB[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketC = _o->bucketC.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketC.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketC[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketD = _o->bucketD.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketD.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketD[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketE = _o->bucketE.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketE.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketE[i].get(), __va->__rehasher); }, &_va ) : 0;
  auto _bucketF = _o->bucketF.size() ? _fbb.CreateVector<flatbuffers::Offset<Tweet>> (_o->bucketF.size(), [](size_t i, _VectorArgs *__va) { return CreateTweet(*__va->__fbb, __va->__o->bucketF[i].get(), __va->__rehasher); }, &_va ) : 0;
  return CreateTweetBin(
      _fbb,
      _bucket0,
      _bucket1,
      _bucket2,
      _bucket3,
      _bucket4,
      _bucket5,
      _bucket6,
      _bucket7,
      _bucket8,
      _bucket9,
      _bucketA,
      _bucketB,
      _bucketC,
      _bucketD,
      _bucketE,
      _bucketF);
}

#endif  // FLATBUFFERS_GENERATED_TWEETBIN_H_

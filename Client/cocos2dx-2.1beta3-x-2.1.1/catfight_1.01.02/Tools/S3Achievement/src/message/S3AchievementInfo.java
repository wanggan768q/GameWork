// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AchievementInfo.proto

package message;

public final class S3AchievementInfo {
  private S3AchievementInfo() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface AchievementInfoOrBuilder
      extends com.google.protobuf.MessageLiteOrBuilder {
    
    // repeated .message.AchievementInfo.AchievementItem achievementArray = 1;
    java.util.List<message.S3AchievementInfo.AchievementInfo.AchievementItem> 
        getAchievementArrayList();
    message.S3AchievementInfo.AchievementInfo.AchievementItem getAchievementArray(int index);
    int getAchievementArrayCount();
  }
  public static final class AchievementInfo extends
      com.google.protobuf.GeneratedMessageLite
      implements AchievementInfoOrBuilder {
    // Use AchievementInfo.newBuilder() to construct.
    private AchievementInfo(Builder builder) {
      super(builder);
    }
    private AchievementInfo(boolean noInit) {}
    
    private static final AchievementInfo defaultInstance;
    public static AchievementInfo getDefaultInstance() {
      return defaultInstance;
    }
    
    public AchievementInfo getDefaultInstanceForType() {
      return defaultInstance;
    }
    
    public interface AchievementItemOrBuilder
        extends com.google.protobuf.MessageLiteOrBuilder {
      
      // required uint32 id = 1;
      boolean hasId();
      int getId();
      
      // required string name = 2;
      boolean hasName();
      String getName();
      
      // required string describ = 3;
      boolean hasDescrib();
      String getDescrib();
    }
    public static final class AchievementItem extends
        com.google.protobuf.GeneratedMessageLite
        implements AchievementItemOrBuilder {
      // Use AchievementItem.newBuilder() to construct.
      private AchievementItem(Builder builder) {
        super(builder);
      }
      private AchievementItem(boolean noInit) {}
      
      private static final AchievementItem defaultInstance;
      public static AchievementItem getDefaultInstance() {
        return defaultInstance;
      }
      
      public AchievementItem getDefaultInstanceForType() {
        return defaultInstance;
      }
      
      private int bitField0_;
      // required uint32 id = 1;
      public static final int ID_FIELD_NUMBER = 1;
      private int id_;
      public boolean hasId() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      public int getId() {
        return id_;
      }
      
      // required string name = 2;
      public static final int NAME_FIELD_NUMBER = 2;
      private java.lang.Object name_;
      public boolean hasName() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      public String getName() {
        java.lang.Object ref = name_;
        if (ref instanceof String) {
          return (String) ref;
        } else {
          com.google.protobuf.ByteString bs = 
              (com.google.protobuf.ByteString) ref;
          String s = bs.toStringUtf8();
          if (com.google.protobuf.Internal.isValidUtf8(bs)) {
            name_ = s;
          }
          return s;
        }
      }
      private com.google.protobuf.ByteString getNameBytes() {
        java.lang.Object ref = name_;
        if (ref instanceof String) {
          com.google.protobuf.ByteString b = 
              com.google.protobuf.ByteString.copyFromUtf8((String) ref);
          name_ = b;
          return b;
        } else {
          return (com.google.protobuf.ByteString) ref;
        }
      }
      
      // required string describ = 3;
      public static final int DESCRIB_FIELD_NUMBER = 3;
      private java.lang.Object describ_;
      public boolean hasDescrib() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      public String getDescrib() {
        java.lang.Object ref = describ_;
        if (ref instanceof String) {
          return (String) ref;
        } else {
          com.google.protobuf.ByteString bs = 
              (com.google.protobuf.ByteString) ref;
          String s = bs.toStringUtf8();
          if (com.google.protobuf.Internal.isValidUtf8(bs)) {
            describ_ = s;
          }
          return s;
        }
      }
      private com.google.protobuf.ByteString getDescribBytes() {
        java.lang.Object ref = describ_;
        if (ref instanceof String) {
          com.google.protobuf.ByteString b = 
              com.google.protobuf.ByteString.copyFromUtf8((String) ref);
          describ_ = b;
          return b;
        } else {
          return (com.google.protobuf.ByteString) ref;
        }
      }
      
      private void initFields() {
        id_ = 0;
        name_ = "";
        describ_ = "";
      }
      private byte memoizedIsInitialized = -1;
      public final boolean isInitialized() {
        byte isInitialized = memoizedIsInitialized;
        if (isInitialized != -1) return isInitialized == 1;
        
        if (!hasId()) {
          memoizedIsInitialized = 0;
          return false;
        }
        if (!hasName()) {
          memoizedIsInitialized = 0;
          return false;
        }
        if (!hasDescrib()) {
          memoizedIsInitialized = 0;
          return false;
        }
        memoizedIsInitialized = 1;
        return true;
      }
      
      public void writeTo(com.google.protobuf.CodedOutputStream output)
                          throws java.io.IOException {
        getSerializedSize();
        if (((bitField0_ & 0x00000001) == 0x00000001)) {
          output.writeUInt32(1, id_);
        }
        if (((bitField0_ & 0x00000002) == 0x00000002)) {
          output.writeBytes(2, getNameBytes());
        }
        if (((bitField0_ & 0x00000004) == 0x00000004)) {
          output.writeBytes(3, getDescribBytes());
        }
      }
      
      private int memoizedSerializedSize = -1;
      public int getSerializedSize() {
        int size = memoizedSerializedSize;
        if (size != -1) return size;
      
        size = 0;
        if (((bitField0_ & 0x00000001) == 0x00000001)) {
          size += com.google.protobuf.CodedOutputStream
            .computeUInt32Size(1, id_);
        }
        if (((bitField0_ & 0x00000002) == 0x00000002)) {
          size += com.google.protobuf.CodedOutputStream
            .computeBytesSize(2, getNameBytes());
        }
        if (((bitField0_ & 0x00000004) == 0x00000004)) {
          size += com.google.protobuf.CodedOutputStream
            .computeBytesSize(3, getDescribBytes());
        }
        memoizedSerializedSize = size;
        return size;
      }
      
      private static final long serialVersionUID = 0L;
      @java.lang.Override
      protected java.lang.Object writeReplace()
          throws java.io.ObjectStreamException {
        return super.writeReplace();
      }
      
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          com.google.protobuf.ByteString data)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return newBuilder().mergeFrom(data).buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          com.google.protobuf.ByteString data,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return newBuilder().mergeFrom(data, extensionRegistry)
                 .buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(byte[] data)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return newBuilder().mergeFrom(data).buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          byte[] data,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return newBuilder().mergeFrom(data, extensionRegistry)
                 .buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(java.io.InputStream input)
          throws java.io.IOException {
        return newBuilder().mergeFrom(input).buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          java.io.InputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        return newBuilder().mergeFrom(input, extensionRegistry)
                 .buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseDelimitedFrom(java.io.InputStream input)
          throws java.io.IOException {
        Builder builder = newBuilder();
        if (builder.mergeDelimitedFrom(input)) {
          return builder.buildParsed();
        } else {
          return null;
        }
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseDelimitedFrom(
          java.io.InputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        Builder builder = newBuilder();
        if (builder.mergeDelimitedFrom(input, extensionRegistry)) {
          return builder.buildParsed();
        } else {
          return null;
        }
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          com.google.protobuf.CodedInputStream input)
          throws java.io.IOException {
        return newBuilder().mergeFrom(input).buildParsed();
      }
      public static message.S3AchievementInfo.AchievementInfo.AchievementItem parseFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        return newBuilder().mergeFrom(input, extensionRegistry)
                 .buildParsed();
      }
      
      public static Builder newBuilder() { return Builder.create(); }
      public Builder newBuilderForType() { return newBuilder(); }
      public static Builder newBuilder(message.S3AchievementInfo.AchievementInfo.AchievementItem prototype) {
        return newBuilder().mergeFrom(prototype);
      }
      public Builder toBuilder() { return newBuilder(this); }
      
      public static final class Builder extends
          com.google.protobuf.GeneratedMessageLite.Builder<
            message.S3AchievementInfo.AchievementInfo.AchievementItem, Builder>
          implements message.S3AchievementInfo.AchievementInfo.AchievementItemOrBuilder {
        // Construct using message.S3AchievementInfo.AchievementInfo.AchievementItem.newBuilder()
        private Builder() {
          maybeForceBuilderInitialization();
        }
        
        private void maybeForceBuilderInitialization() {
        }
        private static Builder create() {
          return new Builder();
        }
        
        public Builder clear() {
          super.clear();
          id_ = 0;
          bitField0_ = (bitField0_ & ~0x00000001);
          name_ = "";
          bitField0_ = (bitField0_ & ~0x00000002);
          describ_ = "";
          bitField0_ = (bitField0_ & ~0x00000004);
          return this;
        }
        
        public Builder clone() {
          return create().mergeFrom(buildPartial());
        }
        
        public message.S3AchievementInfo.AchievementInfo.AchievementItem getDefaultInstanceForType() {
          return message.S3AchievementInfo.AchievementInfo.AchievementItem.getDefaultInstance();
        }
        
        public message.S3AchievementInfo.AchievementInfo.AchievementItem build() {
          message.S3AchievementInfo.AchievementInfo.AchievementItem result = buildPartial();
          if (!result.isInitialized()) {
            throw newUninitializedMessageException(result);
          }
          return result;
        }
        
        private message.S3AchievementInfo.AchievementInfo.AchievementItem buildParsed()
            throws com.google.protobuf.InvalidProtocolBufferException {
          message.S3AchievementInfo.AchievementInfo.AchievementItem result = buildPartial();
          if (!result.isInitialized()) {
            throw newUninitializedMessageException(
              result).asInvalidProtocolBufferException();
          }
          return result;
        }
        
        public message.S3AchievementInfo.AchievementInfo.AchievementItem buildPartial() {
          message.S3AchievementInfo.AchievementInfo.AchievementItem result = new message.S3AchievementInfo.AchievementInfo.AchievementItem(this);
          int from_bitField0_ = bitField0_;
          int to_bitField0_ = 0;
          if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
            to_bitField0_ |= 0x00000001;
          }
          result.id_ = id_;
          if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
            to_bitField0_ |= 0x00000002;
          }
          result.name_ = name_;
          if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
            to_bitField0_ |= 0x00000004;
          }
          result.describ_ = describ_;
          result.bitField0_ = to_bitField0_;
          return result;
        }
        
        public Builder mergeFrom(message.S3AchievementInfo.AchievementInfo.AchievementItem other) {
          if (other == message.S3AchievementInfo.AchievementInfo.AchievementItem.getDefaultInstance()) return this;
          if (other.hasId()) {
            setId(other.getId());
          }
          if (other.hasName()) {
            setName(other.getName());
          }
          if (other.hasDescrib()) {
            setDescrib(other.getDescrib());
          }
          return this;
        }
        
        public final boolean isInitialized() {
          if (!hasId()) {
            
            return false;
          }
          if (!hasName()) {
            
            return false;
          }
          if (!hasDescrib()) {
            
            return false;
          }
          return true;
        }
        
        public Builder mergeFrom(
            com.google.protobuf.CodedInputStream input,
            com.google.protobuf.ExtensionRegistryLite extensionRegistry)
            throws java.io.IOException {
          while (true) {
            int tag = input.readTag();
            switch (tag) {
              case 0:
                
                return this;
              default: {
                if (!parseUnknownField(input, extensionRegistry, tag)) {
                  
                  return this;
                }
                break;
              }
              case 8: {
                bitField0_ |= 0x00000001;
                id_ = input.readUInt32();
                break;
              }
              case 18: {
                bitField0_ |= 0x00000002;
                name_ = input.readBytes();
                break;
              }
              case 26: {
                bitField0_ |= 0x00000004;
                describ_ = input.readBytes();
                break;
              }
            }
          }
        }
        
        private int bitField0_;
        
        // required uint32 id = 1;
        private int id_ ;
        public boolean hasId() {
          return ((bitField0_ & 0x00000001) == 0x00000001);
        }
        public int getId() {
          return id_;
        }
        public Builder setId(int value) {
          bitField0_ |= 0x00000001;
          id_ = value;
          
          return this;
        }
        public Builder clearId() {
          bitField0_ = (bitField0_ & ~0x00000001);
          id_ = 0;
          
          return this;
        }
        
        // required string name = 2;
        private java.lang.Object name_ = "";
        public boolean hasName() {
          return ((bitField0_ & 0x00000002) == 0x00000002);
        }
        public String getName() {
          java.lang.Object ref = name_;
          if (!(ref instanceof String)) {
            String s = ((com.google.protobuf.ByteString) ref).toStringUtf8();
            name_ = s;
            return s;
          } else {
            return (String) ref;
          }
        }
        public Builder setName(String value) {
          if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
          name_ = value;
          
          return this;
        }
        public Builder clearName() {
          bitField0_ = (bitField0_ & ~0x00000002);
          name_ = getDefaultInstance().getName();
          
          return this;
        }
        void setName(com.google.protobuf.ByteString value) {
          bitField0_ |= 0x00000002;
          name_ = value;
          
        }
        
        // required string describ = 3;
        private java.lang.Object describ_ = "";
        public boolean hasDescrib() {
          return ((bitField0_ & 0x00000004) == 0x00000004);
        }
        public String getDescrib() {
          java.lang.Object ref = describ_;
          if (!(ref instanceof String)) {
            String s = ((com.google.protobuf.ByteString) ref).toStringUtf8();
            describ_ = s;
            return s;
          } else {
            return (String) ref;
          }
        }
        public Builder setDescrib(String value) {
          if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000004;
          describ_ = value;
          
          return this;
        }
        public Builder clearDescrib() {
          bitField0_ = (bitField0_ & ~0x00000004);
          describ_ = getDefaultInstance().getDescrib();
          
          return this;
        }
        void setDescrib(com.google.protobuf.ByteString value) {
          bitField0_ |= 0x00000004;
          describ_ = value;
          
        }
        
        // @@protoc_insertion_point(builder_scope:message.AchievementInfo.AchievementItem)
      }
      
      static {
        defaultInstance = new AchievementItem(true);
        defaultInstance.initFields();
      }
      
      // @@protoc_insertion_point(class_scope:message.AchievementInfo.AchievementItem)
    }
    
    // repeated .message.AchievementInfo.AchievementItem achievementArray = 1;
    public static final int ACHIEVEMENTARRAY_FIELD_NUMBER = 1;
    private java.util.List<message.S3AchievementInfo.AchievementInfo.AchievementItem> achievementArray_;
    public java.util.List<message.S3AchievementInfo.AchievementInfo.AchievementItem> getAchievementArrayList() {
      return achievementArray_;
    }
    public java.util.List<? extends message.S3AchievementInfo.AchievementInfo.AchievementItemOrBuilder> 
        getAchievementArrayOrBuilderList() {
      return achievementArray_;
    }
    public int getAchievementArrayCount() {
      return achievementArray_.size();
    }
    public message.S3AchievementInfo.AchievementInfo.AchievementItem getAchievementArray(int index) {
      return achievementArray_.get(index);
    }
    public message.S3AchievementInfo.AchievementInfo.AchievementItemOrBuilder getAchievementArrayOrBuilder(
        int index) {
      return achievementArray_.get(index);
    }
    
    private void initFields() {
      achievementArray_ = java.util.Collections.emptyList();
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized != -1) return isInitialized == 1;
      
      for (int i = 0; i < getAchievementArrayCount(); i++) {
        if (!getAchievementArray(i).isInitialized()) {
          memoizedIsInitialized = 0;
          return false;
        }
      }
      memoizedIsInitialized = 1;
      return true;
    }
    
    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      getSerializedSize();
      for (int i = 0; i < achievementArray_.size(); i++) {
        output.writeMessage(1, achievementArray_.get(i));
      }
    }
    
    private int memoizedSerializedSize = -1;
    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;
    
      size = 0;
      for (int i = 0; i < achievementArray_.size(); i++) {
        size += com.google.protobuf.CodedOutputStream
          .computeMessageSize(1, achievementArray_.get(i));
      }
      memoizedSerializedSize = size;
      return size;
    }
    
    private static final long serialVersionUID = 0L;
    @java.lang.Override
    protected java.lang.Object writeReplace()
        throws java.io.ObjectStreamException {
      return super.writeReplace();
    }
    
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return newBuilder().mergeFrom(data).buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return newBuilder().mergeFrom(data, extensionRegistry)
               .buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return newBuilder().mergeFrom(data).buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return newBuilder().mergeFrom(data, extensionRegistry)
               .buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return newBuilder().mergeFrom(input).buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return newBuilder().mergeFrom(input, extensionRegistry)
               .buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      Builder builder = newBuilder();
      if (builder.mergeDelimitedFrom(input)) {
        return builder.buildParsed();
      } else {
        return null;
      }
    }
    public static message.S3AchievementInfo.AchievementInfo parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      Builder builder = newBuilder();
      if (builder.mergeDelimitedFrom(input, extensionRegistry)) {
        return builder.buildParsed();
      } else {
        return null;
      }
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return newBuilder().mergeFrom(input).buildParsed();
    }
    public static message.S3AchievementInfo.AchievementInfo parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return newBuilder().mergeFrom(input, extensionRegistry)
               .buildParsed();
    }
    
    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(message.S3AchievementInfo.AchievementInfo prototype) {
      return newBuilder().mergeFrom(prototype);
    }
    public Builder toBuilder() { return newBuilder(this); }
    
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          message.S3AchievementInfo.AchievementInfo, Builder>
        implements message.S3AchievementInfo.AchievementInfoOrBuilder {
      // Construct using message.S3AchievementInfo.AchievementInfo.newBuilder()
      private Builder() {
        maybeForceBuilderInitialization();
      }
      
      private void maybeForceBuilderInitialization() {
      }
      private static Builder create() {
        return new Builder();
      }
      
      public Builder clear() {
        super.clear();
        achievementArray_ = java.util.Collections.emptyList();
        bitField0_ = (bitField0_ & ~0x00000001);
        return this;
      }
      
      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }
      
      public message.S3AchievementInfo.AchievementInfo getDefaultInstanceForType() {
        return message.S3AchievementInfo.AchievementInfo.getDefaultInstance();
      }
      
      public message.S3AchievementInfo.AchievementInfo build() {
        message.S3AchievementInfo.AchievementInfo result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }
      
      private message.S3AchievementInfo.AchievementInfo buildParsed()
          throws com.google.protobuf.InvalidProtocolBufferException {
        message.S3AchievementInfo.AchievementInfo result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(
            result).asInvalidProtocolBufferException();
        }
        return result;
      }
      
      public message.S3AchievementInfo.AchievementInfo buildPartial() {
        message.S3AchievementInfo.AchievementInfo result = new message.S3AchievementInfo.AchievementInfo(this);
        int from_bitField0_ = bitField0_;
        if (((bitField0_ & 0x00000001) == 0x00000001)) {
          achievementArray_ = java.util.Collections.unmodifiableList(achievementArray_);
          bitField0_ = (bitField0_ & ~0x00000001);
        }
        result.achievementArray_ = achievementArray_;
        return result;
      }
      
      public Builder mergeFrom(message.S3AchievementInfo.AchievementInfo other) {
        if (other == message.S3AchievementInfo.AchievementInfo.getDefaultInstance()) return this;
        if (!other.achievementArray_.isEmpty()) {
          if (achievementArray_.isEmpty()) {
            achievementArray_ = other.achievementArray_;
            bitField0_ = (bitField0_ & ~0x00000001);
          } else {
            ensureAchievementArrayIsMutable();
            achievementArray_.addAll(other.achievementArray_);
          }
          
        }
        return this;
      }
      
      public final boolean isInitialized() {
        for (int i = 0; i < getAchievementArrayCount(); i++) {
          if (!getAchievementArray(i).isInitialized()) {
            
            return false;
          }
        }
        return true;
      }
      
      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        while (true) {
          int tag = input.readTag();
          switch (tag) {
            case 0:
              
              return this;
            default: {
              if (!parseUnknownField(input, extensionRegistry, tag)) {
                
                return this;
              }
              break;
            }
            case 10: {
              message.S3AchievementInfo.AchievementInfo.AchievementItem.Builder subBuilder = message.S3AchievementInfo.AchievementInfo.AchievementItem.newBuilder();
              input.readMessage(subBuilder, extensionRegistry);
              addAchievementArray(subBuilder.buildPartial());
              break;
            }
          }
        }
      }
      
      private int bitField0_;
      
      // repeated .message.AchievementInfo.AchievementItem achievementArray = 1;
      private java.util.List<message.S3AchievementInfo.AchievementInfo.AchievementItem> achievementArray_ =
        java.util.Collections.emptyList();
      private void ensureAchievementArrayIsMutable() {
        if (!((bitField0_ & 0x00000001) == 0x00000001)) {
          achievementArray_ = new java.util.ArrayList<message.S3AchievementInfo.AchievementInfo.AchievementItem>(achievementArray_);
          bitField0_ |= 0x00000001;
         }
      }
      
      public java.util.List<message.S3AchievementInfo.AchievementInfo.AchievementItem> getAchievementArrayList() {
        return java.util.Collections.unmodifiableList(achievementArray_);
      }
      public int getAchievementArrayCount() {
        return achievementArray_.size();
      }
      public message.S3AchievementInfo.AchievementInfo.AchievementItem getAchievementArray(int index) {
        return achievementArray_.get(index);
      }
      public Builder setAchievementArray(
          int index, message.S3AchievementInfo.AchievementInfo.AchievementItem value) {
        if (value == null) {
          throw new NullPointerException();
        }
        ensureAchievementArrayIsMutable();
        achievementArray_.set(index, value);
        
        return this;
      }
      public Builder setAchievementArray(
          int index, message.S3AchievementInfo.AchievementInfo.AchievementItem.Builder builderForValue) {
        ensureAchievementArrayIsMutable();
        achievementArray_.set(index, builderForValue.build());
        
        return this;
      }
      public Builder addAchievementArray(message.S3AchievementInfo.AchievementInfo.AchievementItem value) {
        if (value == null) {
          throw new NullPointerException();
        }
        ensureAchievementArrayIsMutable();
        achievementArray_.add(value);
        
        return this;
      }
      public Builder addAchievementArray(
          int index, message.S3AchievementInfo.AchievementInfo.AchievementItem value) {
        if (value == null) {
          throw new NullPointerException();
        }
        ensureAchievementArrayIsMutable();
        achievementArray_.add(index, value);
        
        return this;
      }
      public Builder addAchievementArray(
          message.S3AchievementInfo.AchievementInfo.AchievementItem.Builder builderForValue) {
        ensureAchievementArrayIsMutable();
        achievementArray_.add(builderForValue.build());
        
        return this;
      }
      public Builder addAchievementArray(
          int index, message.S3AchievementInfo.AchievementInfo.AchievementItem.Builder builderForValue) {
        ensureAchievementArrayIsMutable();
        achievementArray_.add(index, builderForValue.build());
        
        return this;
      }
      public Builder addAllAchievementArray(
          java.lang.Iterable<? extends message.S3AchievementInfo.AchievementInfo.AchievementItem> values) {
        ensureAchievementArrayIsMutable();
        super.addAll(values, achievementArray_);
        
        return this;
      }
      public Builder clearAchievementArray() {
        achievementArray_ = java.util.Collections.emptyList();
        bitField0_ = (bitField0_ & ~0x00000001);
        
        return this;
      }
      public Builder removeAchievementArray(int index) {
        ensureAchievementArrayIsMutable();
        achievementArray_.remove(index);
        
        return this;
      }
      
      // @@protoc_insertion_point(builder_scope:message.AchievementInfo)
    }
    
    static {
      defaultInstance = new AchievementInfo(true);
      defaultInstance.initFields();
    }
    
    // @@protoc_insertion_point(class_scope:message.AchievementInfo)
  }
  
  
  static {
  }
  
  // @@protoc_insertion_point(outer_class_scope)
}
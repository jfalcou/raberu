<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.16.1" doxygen_gitid="669aeeefca743c148e2d935b3d3c69535c7491e6">
  <compound kind="struct">
    <name>rbr::any_keyword</name>
    <filename>structrbr_1_1any__keyword.html</filename>
    <templarg>typename ID</templarg>
    <base>rbr::as_keyword&lt; any_keyword&lt; ID &gt; &gt;</base>
    <member kind="typedef">
      <type>ID</type>
      <name>id_type</name>
      <anchorfile>structrbr_1_1any__keyword.html</anchorfile>
      <anchor>a461dbb4071e3311a7e99d1ee498eaed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>any_keyword&lt; ID &gt;</type>
      <name>tag_type</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a11a66e7b3ce8c54853f238c99de6ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>operator()</name>
      <anchorfile>structrbr_1_1as__keyword_a40466d5e41a179d4ba59dc36ba2ee36b.html</anchorfile>
      <anchor>a40466d5e41a179d4ba59dc36ba2ee36b</anchor>
      <arglist>(Os &amp;&amp;... o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>ad8afe5ffee5a87a2dea65e75d8f9c501</anchor>
      <arglist>(as_keyword const &amp;) const noexcept=default</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator|</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a2fb398268d0ca74637047903a9ed20e8</anchor>
      <arglist>(Type &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>show</name>
      <anchorfile>structrbr_1_1as__keyword_aa5f2825b11a01b5cf8680759d8bf6177.html</anchorfile>
      <anchor>aa5f2825b11a01b5cf8680759d8bf6177</anchor>
      <arglist>(std::ostream &amp;os, V const &amp;v) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>accept</name>
      <anchorfile>structrbr_1_1as__keyword_ae5420c9dd19d328b53c23f2768b4a7df.html</anchorfile>
      <anchor>ae5420c9dd19d328b53c23f2768b4a7df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr any_keyword&lt; ID &gt;</type>
      <name>keyword</name>
      <anchorfile>group__kwds_ga111cd0aae8b0ddc48b0682cb57be4601.html</anchorfile>
      <anchor>ga111cd0aae8b0ddc48b0682cb57be4601</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&quot;&quot;_kw</name>
      <anchorfile>group__udls_ga86a979e01a966f4538cedfd2082bc797.html</anchorfile>
      <anchor>ga86a979e01a966f4538cedfd2082bc797</anchor>
      <arglist>() noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::as_keyword</name>
    <filename>structrbr_1_1as__keyword.html</filename>
    <templarg>typename Keyword</templarg>
    <member kind="typedef">
      <type>Keyword</type>
      <name>tag_type</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a11a66e7b3ce8c54853f238c99de6ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>operator()</name>
      <anchorfile>structrbr_1_1as__keyword_a40466d5e41a179d4ba59dc36ba2ee36b.html</anchorfile>
      <anchor>a40466d5e41a179d4ba59dc36ba2ee36b</anchor>
      <arglist>(Os &amp;&amp;... o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>ad8afe5ffee5a87a2dea65e75d8f9c501</anchor>
      <arglist>(as_keyword const &amp;) const noexcept=default</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator=</name>
      <anchorfile>structrbr_1_1as__keyword_a409f2a5335b450e52586bf33217136cf.html</anchorfile>
      <anchor>a409f2a5335b450e52586bf33217136cf</anchor>
      <arglist>(Type &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator|</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a5031419f90500aea0ff2176ba8c4ec75</anchor>
      <arglist>(call&lt; Func &gt; &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator|</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a2fb398268d0ca74637047903a9ed20e8</anchor>
      <arglist>(Type &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>show</name>
      <anchorfile>structrbr_1_1as__keyword_aa5f2825b11a01b5cf8680759d8bf6177.html</anchorfile>
      <anchor>aa5f2825b11a01b5cf8680759d8bf6177</anchor>
      <arglist>(std::ostream &amp;os, V const &amp;v) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>accept</name>
      <anchorfile>structrbr_1_1as__keyword_ae5420c9dd19d328b53c23f2768b4a7df.html</anchorfile>
      <anchor>ae5420c9dd19d328b53c23f2768b4a7df</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::call</name>
    <filename>structrbr_1_1call.html</filename>
    <templarg>typename Func</templarg>
  </compound>
  <compound kind="struct">
    <name>rbr::checked_keyword</name>
    <filename>structrbr_1_1checked__keyword.html</filename>
    <templarg>typename ID</templarg>
    <templarg>template&lt; class &gt; class Checker</templarg>
    <base>rbr::as_keyword&lt; checked_keyword&lt; ID, Checker &gt; &gt;</base>
    <member kind="typedef">
      <type>checked_keyword&lt; ID, Checker &gt;</type>
      <name>tag_type</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a11a66e7b3ce8c54853f238c99de6ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>operator()</name>
      <anchorfile>structrbr_1_1as__keyword_a40466d5e41a179d4ba59dc36ba2ee36b.html</anchorfile>
      <anchor>a40466d5e41a179d4ba59dc36ba2ee36b</anchor>
      <arglist>(Os &amp;&amp;... o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>ad8afe5ffee5a87a2dea65e75d8f9c501</anchor>
      <arglist>(as_keyword const &amp;) const noexcept=default</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator|</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a2fb398268d0ca74637047903a9ed20e8</anchor>
      <arglist>(Type &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>show</name>
      <anchorfile>structrbr_1_1as__keyword_aa5f2825b11a01b5cf8680759d8bf6177.html</anchorfile>
      <anchor>aa5f2825b11a01b5cf8680759d8bf6177</anchor>
      <arglist>(std::ostream &amp;os, V const &amp;v) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>accept</name>
      <anchorfile>structrbr_1_1as__keyword_ae5420c9dd19d328b53c23f2768b4a7df.html</anchorfile>
      <anchor>ae5420c9dd19d328b53c23f2768b4a7df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr checked_keyword&lt; ID, Checker &gt;</type>
      <name>keyword</name>
      <anchorfile>group__kwds_ga1defddc866f08ffe48f8cede54d6c662.html</anchorfile>
      <anchor>ga1defddc866f08ffe48f8cede54d6c662</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::flag_keyword</name>
    <filename>structrbr_1_1flag__keyword.html</filename>
    <templarg>typename ID</templarg>
    <member kind="typedef">
      <type>ID</type>
      <name>id_type</name>
      <anchorfile>structrbr_1_1flag__keyword.html</anchorfile>
      <anchor>a131e22636296d01c1051cdbf0481cd15</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr flag_keyword&lt; Tag &gt;</type>
      <name>flag</name>
      <anchorfile>group__kwds_ga582ef0aad9a0b99f141d2ba30828ec18.html</anchorfile>
      <anchor>ga582ef0aad9a0b99f141d2ba30828ec18</anchor>
      <arglist>(Tag id) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&quot;&quot;_fl</name>
      <anchorfile>group__udls_ga0cdec845c68884472bb41b79f7912db5.html</anchorfile>
      <anchor>ga0cdec845c68884472bb41b79f7912db5</anchor>
      <arglist>() noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::id_</name>
    <filename>structrbr_1_1id__.html</filename>
    <templarg>literals::str ID</templarg>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structrbr_1_1id__.html</anchorfile>
      <anchor>a03cbd55c3ba6e14c5ab15862d1332f76</anchor>
      <arglist>(std::ostream &amp;os, id_ const &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::is_equivalent</name>
    <filename>structrbr_1_1is__equivalent.html</filename>
    <templarg>concepts::settings S1</templarg>
    <templarg>concepts::settings S2</templarg>
  </compound>
  <compound kind="struct">
    <name>rbr::option</name>
    <filename>structrbr_1_1option.html</filename>
    <templarg>concepts::keyword Keyword</templarg>
    <templarg>typename Value</templarg>
  </compound>
  <compound kind="struct">
    <name>rbr::settings</name>
    <filename>structrbr_1_1settings.html</filename>
    <templarg>concepts::option... Opts</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structrbr_1_1settings.html</anchorfile>
      <anchor>a5bc5ef4b0ceaab6e6db072f1cbb15473</anchor>
      <arglist>(flag_keyword&lt; Keyword &gt; const &amp;) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structrbr_1_1settings_ae0298902e927c3477caae7057002f477.html</anchorfile>
      <anchor>ae0298902e927c3477caae7057002f477</anchor>
      <arglist>(Key const &amp;k) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator[]</name>
      <anchorfile>structrbr_1_1settings.html</anchorfile>
      <anchor>a06272618f4baa0960b8946203194293f</anchor>
      <arglist>(raberu_implementation_defined const &amp;tgt) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr</type>
      <name>settings</name>
      <anchorfile>structrbr_1_1settings.html</anchorfile>
      <anchor>a0f2ff35651fc48a756885b73568d0a57</anchor>
      <arglist>(Opts const &amp;... opts)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>contains</name>
      <anchorfile>structrbr_1_1settings_a7a99be5f170a42c9af2ce44ab368fe8a.html</anchorfile>
      <anchor>a7a99be5f170a42c9af2ce44ab368fe8a</anchor>
      <arglist>(Key const &amp;kw) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>contains_any</name>
      <anchorfile>structrbr_1_1settings_af0ba5c226275e238abf83b15f463f77d.html</anchorfile>
      <anchor>af0ba5c226275e238abf83b15f463f77d</anchor>
      <arglist>(Keys... ks) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>contains_none</name>
      <anchorfile>structrbr_1_1settings_a1c758db63574313d7308f978a0e92e6c.html</anchorfile>
      <anchor>a1c758db63574313d7308f978a0e92e6c</anchor>
      <arglist>(Keys... ks) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr auto</type>
      <name>contains_only</name>
      <anchorfile>structrbr_1_1settings_afa76f4135cb4516fa6641c0d3a5758d9.html</anchorfile>
      <anchor>afa76f4135cb4516fa6641c0d3a5758d9</anchor>
      <arglist>(Keys const &amp;... ks) noexcept</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr std::ptrdiff_t</type>
      <name>size</name>
      <anchorfile>structrbr_1_1settings.html</anchorfile>
      <anchor>ab63f0b741fbc37f174f679cf70239bf6</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>drop</name>
      <anchorfile>group__stng_gad36681b05136221ae61651ccbc4b3ddb.html</anchorfile>
      <anchor>gad36681b05136221ae61651ccbc4b3ddb</anchor>
      <arglist>(K const &amp;k, settings&lt; O... &gt; const &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>merge</name>
      <anchorfile>group__stng_ga39cbfeb49cdec50141e18847dde121da.html</anchorfile>
      <anchor>ga39cbfeb49cdec50141e18847dde121da</anchor>
      <arglist>(settings&lt; K1s... &gt; const &amp;opts, settings&lt; K2s... &gt; const &amp;defs) noexcept</arglist>
    </member>
    <member kind="friend">
      <type>friend std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structrbr_1_1settings.html</anchorfile>
      <anchor>aa9f57c3d2450b6a37528b819ad0c84fd</anchor>
      <arglist>(std::ostream &amp;os, settings const &amp;s)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::literals::str</name>
    <filename>structrbr_1_1literals_1_1str.html</filename>
  </compound>
  <compound kind="struct">
    <name>rbr::typed_keyword</name>
    <filename>structrbr_1_1typed__keyword.html</filename>
    <templarg>typename ID</templarg>
    <templarg>typename Type</templarg>
    <base>rbr::as_keyword&lt; typed_keyword&lt; ID, Type &gt; &gt;</base>
    <member kind="typedef">
      <type>typed_keyword&lt; ID, Type &gt;</type>
      <name>tag_type</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a11a66e7b3ce8c54853f238c99de6ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>operator()</name>
      <anchorfile>structrbr_1_1as__keyword_a40466d5e41a179d4ba59dc36ba2ee36b.html</anchorfile>
      <anchor>a40466d5e41a179d4ba59dc36ba2ee36b</anchor>
      <arglist>(Os &amp;&amp;... o) const</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&lt;=&gt;</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>ad8afe5ffee5a87a2dea65e75d8f9c501</anchor>
      <arglist>(as_keyword const &amp;) const noexcept=default</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator|</name>
      <anchorfile>structrbr_1_1as__keyword.html</anchorfile>
      <anchor>a2fb398268d0ca74637047903a9ed20e8</anchor>
      <arglist>(Type &amp;&amp;v) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>show</name>
      <anchorfile>structrbr_1_1as__keyword_aa5f2825b11a01b5cf8680759d8bf6177.html</anchorfile>
      <anchor>aa5f2825b11a01b5cf8680759d8bf6177</anchor>
      <arglist>(std::ostream &amp;os, V const &amp;v) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr bool</type>
      <name>accept</name>
      <anchorfile>structrbr_1_1as__keyword_ae5420c9dd19d328b53c23f2768b4a7df.html</anchorfile>
      <anchor>ae5420c9dd19d328b53c23f2768b4a7df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>constexpr typed_keyword&lt; ID, Type &gt;</type>
      <name>keyword</name>
      <anchorfile>group__kwds_ga22ca1174daaba7df70425196133e015d.html</anchorfile>
      <anchor>ga22ca1174daaba7df70425196133e015d</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rbr::types</name>
    <filename>structrbr_1_1types.html</filename>
    <templarg>typename... T</templarg>
  </compound>
  <compound kind="struct">
    <name>rbr::unknown_key</name>
    <filename>structrbr_1_1unknown__key.html</filename>
  </compound>
  <compound kind="concept">
    <name>rbr::concepts::exactly</name>
    <filename>conceptrbr_1_1concepts_1_1exactly.html</filename>
  </compound>
  <compound kind="concept">
    <name>rbr::concepts::keyword</name>
    <filename>conceptrbr_1_1concepts_1_1keyword.html</filename>
  </compound>
  <compound kind="concept">
    <name>rbr::concepts::option</name>
    <filename>conceptrbr_1_1concepts_1_1option.html</filename>
  </compound>
  <compound kind="concept">
    <name>rbr::concepts::settings</name>
    <filename>conceptrbr_1_1concepts_1_1settings.html</filename>
  </compound>
  <compound kind="namespace">
    <name>rbr</name>
    <filename>namespacerbr.html</filename>
    <namespace>rbr::concepts</namespace>
    <namespace>rbr::literals</namespace>
    <namespace>rbr::result</namespace>
    <class kind="struct">rbr::any_keyword</class>
    <class kind="struct">rbr::as_keyword</class>
    <class kind="struct">rbr::call</class>
    <class kind="struct">rbr::checked_keyword</class>
    <class kind="struct">rbr::flag_keyword</class>
    <class kind="struct">rbr::id_</class>
    <class kind="struct">rbr::is_equivalent</class>
    <class kind="struct">rbr::option</class>
    <class kind="struct">rbr::settings</class>
    <class kind="struct">rbr::typed_keyword</class>
    <class kind="struct">rbr::types</class>
    <class kind="struct">rbr::unknown_key</class>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>fetch</name>
      <anchorfile>group__stng_gab9ee73c2f143fc87e4f572624d671f29.html</anchorfile>
      <anchor>gab9ee73c2f143fc87e4f572624d671f29</anchor>
      <arglist>(K const &amp;k, Os const &amp;... os)</arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>fetch</name>
      <anchorfile>namespacerbr.html</anchorfile>
      <anchor>a728a418a00e14abba03b4924d897f200</anchor>
      <arglist>(K const &amp;k, Settings const &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>fetch</name>
      <anchorfile>namespacerbr.html</anchorfile>
      <anchor>a1fcfa44191016fc6588ed35ffeb652cc</anchor>
      <arglist>(raberu_implementation_defined const &amp;k, Os const &amp;... os)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>keywords</name>
      <anchorfile>group__stng_ga896526026e355f76431a11b9b06a0d48.html</anchorfile>
      <anchor>ga896526026e355f76431a11b9b06a0d48</anchor>
      <arglist>(rbr::settings&lt; Opts... &gt; const &amp;s)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>settings</name>
      <anchorfile>namespacerbr.html</anchorfile>
      <anchor>ae9bbf50288a429ab1d6048bdb85493e0</anchor>
      <arglist>(Opts const &amp;... opts) -&gt; settings&lt; Opts... &gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>values</name>
      <anchorfile>group__stng_ga3f22cab5c8d14abf79568a123cdc4dfd.html</anchorfile>
      <anchor>ga3f22cab5c8d14abf79568a123cdc4dfd</anchor>
      <arglist>(rbr::settings&lt; Opts... &gt; const &amp;s)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>rbr::concepts</name>
    <filename>namespacerbr_1_1concepts.html</filename>
    <concept>rbr::concepts::exactly</concept>
    <concept>rbr::concepts::keyword</concept>
    <concept>rbr::concepts::option</concept>
    <concept>rbr::concepts::settings</concept>
  </compound>
  <compound kind="namespace">
    <name>rbr::literals</name>
    <filename>namespacerbr_1_1literals.html</filename>
    <class kind="struct">rbr::literals::str</class>
    <member kind="function">
      <type>constexpr auto</type>
      <name>operator&quot;&quot;_id</name>
      <anchorfile>group__udls_ga8b614b5edfe2ff77c9165656ba9a7dfe.html</anchorfile>
      <anchor>ga8b614b5edfe2ff77c9165656ba9a7dfe</anchor>
      <arglist>() noexcept</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>rbr::result</name>
    <filename>namespacerbr_1_1result.html</filename>
  </compound>
  <compound kind="group">
    <name>utility</name>
    <title>Helper types and function</title>
    <filename>group__utility.html</filename>
    <subgroup>udls</subgroup>
    <class kind="struct">rbr::id_</class>
    <class kind="struct">rbr::literals::str</class>
    <class kind="struct">rbr::types</class>
  </compound>
  <compound kind="group">
    <name>kwds</name>
    <title>Keywords definitions and handling</title>
    <filename>group__kwds.html</filename>
    <class kind="struct">rbr::any_keyword</class>
    <class kind="struct">rbr::as_keyword</class>
    <class kind="struct">rbr::call</class>
    <class kind="struct">rbr::checked_keyword</class>
    <class kind="struct">rbr::flag_keyword</class>
    <class kind="struct">rbr::typed_keyword</class>
    <member kind="function">
      <type>constexpr flag_keyword&lt; Tag &gt;</type>
      <name>rbr::flag_keyword::flag</name>
      <anchorfile>group__kwds_ga582ef0aad9a0b99f141d2ba30828ec18.html</anchorfile>
      <anchor>ga582ef0aad9a0b99f141d2ba30828ec18</anchor>
      <arglist>(Tag id) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr any_keyword&lt; ID &gt;</type>
      <name>rbr::any_keyword::keyword</name>
      <anchorfile>group__kwds_ga111cd0aae8b0ddc48b0682cb57be4601.html</anchorfile>
      <anchor>ga111cd0aae8b0ddc48b0682cb57be4601</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr checked_keyword&lt; ID, Checker &gt;</type>
      <name>rbr::checked_keyword::keyword</name>
      <anchorfile>group__kwds_ga1defddc866f08ffe48f8cede54d6c662.html</anchorfile>
      <anchor>ga1defddc866f08ffe48f8cede54d6c662</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr typed_keyword&lt; ID, Type &gt;</type>
      <name>rbr::typed_keyword::keyword</name>
      <anchorfile>group__kwds_ga22ca1174daaba7df70425196133e015d.html</anchorfile>
      <anchor>ga22ca1174daaba7df70425196133e015d</anchor>
      <arglist>(ID id) noexcept</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>main</name>
    <title>Main RABERU components</title>
    <filename>group__main.html</filename>
    <subgroup>kwds</subgroup>
    <subgroup>stng</subgroup>
  </compound>
  <compound kind="group">
    <name>stng</name>
    <title>Settings definitions and handling</title>
    <filename>group__stng.html</filename>
    <class kind="struct">rbr::is_equivalent</class>
    <class kind="struct">rbr::option</class>
    <class kind="struct">rbr::settings</class>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::settings::drop</name>
      <anchorfile>group__stng_gad36681b05136221ae61651ccbc4b3ddb.html</anchorfile>
      <anchor>gad36681b05136221ae61651ccbc4b3ddb</anchor>
      <arglist>(K const &amp;k, settings&lt; O... &gt; const &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>constexpr decltype(auto)</type>
      <name>rbr::fetch</name>
      <anchorfile>group__stng_gab9ee73c2f143fc87e4f572624d671f29.html</anchorfile>
      <anchor>gab9ee73c2f143fc87e4f572624d671f29</anchor>
      <arglist>(K const &amp;k, Os const &amp;... os)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::keywords</name>
      <anchorfile>group__stng_ga896526026e355f76431a11b9b06a0d48.html</anchorfile>
      <anchor>ga896526026e355f76431a11b9b06a0d48</anchor>
      <arglist>(rbr::settings&lt; Opts... &gt; const &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::settings::merge</name>
      <anchorfile>group__stng_ga39cbfeb49cdec50141e18847dde121da.html</anchorfile>
      <anchor>ga39cbfeb49cdec50141e18847dde121da</anchor>
      <arglist>(settings&lt; K1s... &gt; const &amp;opts, settings&lt; K2s... &gt; const &amp;defs) noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::values</name>
      <anchorfile>group__stng_ga3f22cab5c8d14abf79568a123cdc4dfd.html</anchorfile>
      <anchor>ga3f22cab5c8d14abf79568a123cdc4dfd</anchor>
      <arglist>(rbr::settings&lt; Opts... &gt; const &amp;s)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>udls</name>
    <title>User-defined Literal operators</title>
    <filename>group__udls.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::flag_keyword::operator&quot;&quot;_fl</name>
      <anchorfile>group__udls_ga0cdec845c68884472bb41b79f7912db5.html</anchorfile>
      <anchor>ga0cdec845c68884472bb41b79f7912db5</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::literals::operator&quot;&quot;_id</name>
      <anchorfile>group__udls_ga8b614b5edfe2ff77c9165656ba9a7dfe.html</anchorfile>
      <anchor>ga8b614b5edfe2ff77c9165656ba9a7dfe</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>rbr::any_keyword::operator&quot;&quot;_kw</name>
      <anchorfile>group__udls_ga86a979e01a966f4538cedfd2082bc797.html</anchorfile>
      <anchor>ga86a979e01a966f4538cedfd2082bc797</anchor>
      <arglist>() noexcept</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>changelog</name>
    <title>Change Log</title>
    <filename>changelog.html</filename>
    <docanchor file="changelog.html" title="/__w/raberu/raberu/doc/changelog.md">md__2____w_2raberu_2raberu_2doc_2changelog</docanchor>
  </compound>
  <compound kind="page">
    <name>custom</name>
    <title>Tutorial: Customizing Keyword</title>
    <filename>custom.html</filename>
    <docanchor file="custom.html" title="Using Pre-bound keyword">custom_01</docanchor>
    <docanchor file="custom.html" title="Custom RABERU Keywords">custom_02</docanchor>
    <docanchor file="custom.html" title="Extending RABERU Keywords">custom-extension</docanchor>
    <docanchor file="custom.html" title="Custom Keywords Display">custom-display</docanchor>
  </compound>
  <compound kind="page">
    <name>licence</name>
    <title>Licence</title>
    <filename>licence.html</filename>
    <docanchor file="licence.html" title="/__w/raberu/raberu/doc/licence.md">md__2____w_2raberu_2raberu_2doc_2licence</docanchor>
  </compound>
  <compound kind="page">
    <name>setup</name>
    <title>Setup</title>
    <filename>setup.html</filename>
    <docanchor file="setup.html" title="Install from the source">setup-source</docanchor>
    <docanchor file="setup.html" title="Standalone setup">setup-standalone</docanchor>
    <docanchor file="setup.html" title="CMake FetchContent">setup-fetchcontent</docanchor>
    <docanchor file="setup.html" title="Setup with CPM">setup-cpm</docanchor>
  </compound>
  <compound kind="page">
    <name>tutorial</name>
    <title>RABERU 101</title>
    <filename>tutorial.html</filename>
    <docanchor file="tutorial.html" title="Keyword, Options, Settings">tutorial_01</docanchor>
    <docanchor file="tutorial.html" title="Flavor of Keywords">tutorial_02</docanchor>
    <docanchor file="tutorial.html" title="Regular keywords">tutorial-keywords</docanchor>
    <docanchor file="tutorial.html" title="Flags">tutorial-flags</docanchor>
    <docanchor file="tutorial.html" title="Checked keywords">tutorial-checked</docanchor>
    <docanchor file="tutorial.html" title="Settings">tutorial_03</docanchor>
    <docanchor file="tutorial.html" title="Defining a Settings">tutorial-settings</docanchor>
    <docanchor file="tutorial.html" title="Stream insertion">tutorial-stream</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>The Fancy Named Parameters Library</title>
    <filename>index.html</filename>
  </compound>
</tagfile>
